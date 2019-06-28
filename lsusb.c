//
// Created by Knight on 2019-06-20.
//

#include <libusb.h>
#include <stdio.h>
#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>

#define DP
//#undef DP

struct string {
    char *ptr;
    size_t len;
};

void init_string(struct string *s);

size_t get_usb_ids(struct string s);

int main(int argc, char **argv) {

    struct string s;
    init_string(&s);
    get_usb_ids(s);


    int r = libusb_init(NULL);
    if (r < 0) {
        fprintf(stderr, "libusb_init error: %d", r);
        return r;
    }

    libusb_device **devs = NULL;
    ssize_t ret = libusb_get_device_list(NULL, &devs);
    if (ret < 0) {
        fprintf(stderr, "libusb_get_device_list: %ld", ret);
        libusb_exit(NULL);
        return ret;
    }

#ifdef DP
    printf("found %ld devices\n", ret);
#endif
    for (int i = 0; devs[i] != NULL; i++) {
//Bus 002 Device 001: ID 1d6b:0003 Linux Foundation 3.0 root hub

        struct libusb_device_descriptor desc;
        r = libusb_get_device_descriptor(devs[i], &desc);
        if (r < 0) {
            fprintf(stderr, "libusb_get_device_descriptor: %d", r);
            continue; // skip
        }

        printf("Bus %03d Device %03d: ID %04x:%04x\n",
               libusb_get_bus_number(devs[i]),
               libusb_get_device_address(devs[i]),
               desc.idVendor, desc.idProduct);
    }


    libusb_free_device_list(devs, 1);
    libusb_exit(NULL);
    return 0;
}

void init_string(struct string *s) {
    s->len = 0;
    s->ptr = malloc(s->len + 1);
    if (s->ptr == NULL) {
        fprintf(stderr, "malloc() failed\n");
        exit(EXIT_FAILURE);
    }
    s->ptr[0] = '\0';
}

size_t write_function(void *ptr, size_t size, size_t nmemb, struct string *s) {
//    printf("DP(%ld): %s\nStream(%ld): %s\n", size, ptr, nmemb, stream);
//    return 0;
//    printf("%d", atoi(ptr));
    size_t new_len = s->len + size * nmemb;
    s->ptr = realloc(s->ptr, new_len + 1);
    if (s->ptr == NULL) {
        fprintf(stderr, "realloc() failed\n");
        exit(EXIT_FAILURE);
    }
    memcpy(s->ptr + s->len, ptr, size * nmemb);
    s->ptr[new_len] = '\0';
    s->len = new_len;
    return size * nmemb;
}

size_t get_usb_ids(struct string s) {
    CURL *curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://www.linux-usb.org/usb.ids");

        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3L);
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 10L); //连接超时时长
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_function);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);

        curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");

        /* Perform the request, res will get the return code */
        CURLcode res = curl_easy_perform(curl);
        /* Check for errors */
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));

        printf("============\n%s\n============\n", s.ptr);
        free(s.ptr);
        s.ptr = NULL;
        /* always cleanup */
        curl_easy_cleanup(curl);
    }
}