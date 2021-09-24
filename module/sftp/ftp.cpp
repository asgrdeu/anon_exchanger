//
// Created by Михаил Евпатов on 22.09.2021.
//

#include "ftp.h"

struct FtpFile {
    const char *filename;
    FILE *stream;
};

long int progress = 0;
long int full_file_size = 0;
long int file_size_counter = 0;

static size_t read_callback(const char *ptr, size_t size, size_t nmemb, FILE *stream) {
    curl_off_t nread;

    size_t retcode = fread((void *) ptr, size, nmemb, stream);

    nread = (curl_off_t)retcode;

    progress += nread;

    if (retcode == nread && file_size_counter % 1000 == 0)
        printf("Uploaded %ld/%" CURL_FORMAT_CURL_OFF_T
                    " bytes from file.\n", progress, full_file_size);
    file_size_counter++;
    return retcode;
}

bool upload(const std::string& url, const std::string& local_path, const std::string& remote_path, const std::string& upload_us, const std::string& rename_to) {
    std::string cmd_upload_us = "RNFR " + upload_us;
    std::string cmd_rename_to = "RNTO " + rename_to;

    CURL *curl;
    CURLcode res = CURLE_OK;
    FILE *hd_src;
    struct stat file_info{};
    curl_off_t fsize;

    struct curl_slist *headerlist = nullptr;
    static const char* buf_1 = cmd_upload_us.c_str();
    static const char* buf_2 = cmd_rename_to.c_str();

    /* get the file size of the local file */
    if (stat(local_path.c_str(), &file_info)) {
        printf("Couldn't open '%s': %s\n", local_path.c_str(), strerror(errno));
        return false;
    }
    fsize = (curl_off_t) file_info.st_size;
    full_file_size = (curl_off_t) file_info.st_size;

    printf("Local file size: %" CURL_FORMAT_CURL_OFF_T " bytes.\n", fsize);

/* get a FILE * of the same file */
    hd_src = fopen(local_path.c_str(), "rb");

/* In windows, this will init the winsock stuff */
    curl_global_init(CURL_GLOBAL_ALL);

/* get a curl handle */
    curl = curl_easy_init();
    if (curl) {
/* build a list of commands to pass to libcurl */
        headerlist = curl_slist_append(headerlist, buf_1);
        headerlist = curl_slist_append(headerlist, buf_2);

/* we want to use our own read function */
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);

/* enable uploading */
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

/* specify target */
        curl_easy_setopt(curl, CURLOPT_URL, (url + upload_us).c_str());

/* pass in that last of FTP commands to run after the transfer */
        curl_easy_setopt(curl, CURLOPT_POSTQUOTE, headerlist);

/* now specify which file to upload */
        curl_easy_setopt(curl, CURLOPT_READDATA, hd_src);

/* Set the size of the file to upload (optional).  If you give a *_LARGE
   option you MUST make sure that the type of the passed-in argument is a
   curl_off_t. If you use CURLOPT_INFILESIZE (without _LARGE) you must
   make sure that to pass in a type 'long' argument. */
        curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE,
                         (curl_off_t) fsize);

/* Now run off and do what you've been told! */
        res = curl_easy_perform(curl);
/* Check for errors */
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));

/* clean up the FTP commands list */
        curl_slist_free_all(headerlist);

/* always cleanup */
        curl_easy_cleanup(curl);
    }
    fclose(hd_src); /* close the local file */

    curl_global_cleanup();

    progress = 0;
    file_size_counter = 0;
    return res == CURLE_OK && curl;
}

static size_t my_fwrite(void *buffer, size_t size, size_t nmemb, void *stream) {
    auto *out = (struct FtpFile *)stream;
    if(!out->stream) {
        /* open file for writing */
        out->stream = fopen(out->filename, "wb");
        if(!out->stream)
            return -1; /* failure, can't open file to write */
    }
    return fwrite(buffer, size, nmemb, out->stream);
}


int download(const std::string& id, const std::string& url) {
    CURL *curl;
    CURLcode res;
    struct FtpFile ftpfile = {
            id.c_str(), /* name to store the file as if successful */
            nullptr
    };

    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL,(url + id).c_str());
        /* Define our callback to get called when there's data to be written */
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_fwrite);
        /* Set a pointer to our struct to pass to the callback */
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ftpfile);

        /* Switch on full protocol/debug output */
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        res = curl_easy_perform(curl);

        /* always cleanup */
        curl_easy_cleanup(curl);

        if(CURLE_OK != res) {
            /* we failed */
            printf("curl told us %d\n", res);
        }
    }

    if(ftpfile.stream)
        fclose(ftpfile.stream); /* close the local file */

    curl_global_cleanup();

    return 0;
}