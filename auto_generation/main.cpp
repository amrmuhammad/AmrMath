#include <iostream>
#include <string>
#include <curl/curl.h> // Include the libcurl header

int main() {
    CURL *curl;
    FILE *fp;
    CURLcode res;
    const char *url = "https://en.wikipedia.org/wiki/Algebraic_expression"; // Replace with your URL
    const char *output_filename = "downloaded_file.txt";

    curl_global_init(CURL_GLOBAL_DEFAULT); // Initialize libcurl global resources

    curl = curl_easy_init(); // Create a CURL easy handle
    if (curl) {
        fp = fopen(output_filename, "wb"); // Open file for writing in binary mode
        if (fp == NULL) {
            std::cerr << "Error opening output file!" << std::endl;
            curl_easy_cleanup(curl);
            curl_global_cleanup();
            return 1;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url); // Set the URL
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL); // Use default write function
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp); // Set output file pointer

        res = curl_easy_perform(curl); // Perform the download
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            std::cout << "File downloaded successfully to " << output_filename << std::endl;
        }

        fclose(fp); // Close the output file
        curl_easy_cleanup(curl); // Clean up the CURL easy handle
    } else {
        std::cerr << "Error initializing libcurl!" << std::endl;
    }

    curl_global_cleanup(); // Clean up libcurl global resources
    return 0;
}
