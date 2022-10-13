//
// Created by jamal on 30/08/2022.
//
#include "download_file.h"

#include <curl/curl.h>
#include <utils/string_utils.h>
#include <core/logging.h>

#include <iostream>

#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

using namespace std;

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb,
                                  void *userp) {
    size_t realsize = size * nmemb;
    auto &mem = *static_cast<std::string *>(userp);
    mem.append(static_cast<char *>(contents), realsize);
    return realsize;
}

void write_file(const fs::path &path, const string &content) {
    BOOST_LOG_TRIVIAL(trace) << "writing content to file " << path;
    std::ofstream out(path, ios::binary);
    out << content;
    out.close();
}

vector<uint8_t> read_file(const fs::path &path) {
    BOOST_LOG_TRIVIAL(trace) << "initiating read content from file " << path;
    ifstream file(path, ios::binary | ios::ate);
    streamsize size = file.tellg();
    file.seekg(0, ios::beg);

    vector<char> v1(size);

    BOOST_LOG_TRIVIAL(trace) << "reading content from file " << path;
    file.read(v1.data(), size);

    std::vector<uint8_t> buffer;
    std::copy(v1.begin(), v1.end(), std::back_inserter(buffer));

    BOOST_LOG_TRIVIAL(trace) << "file was read successfully with size " << buffer.size();
    return buffer;
}

vector<uint8_t> object_detector::utils::download_file_from_url(const string &url) {
    BOOST_LOG_TRIVIAL(debug) << "downloading file from url " << url;

    auto u_path = fs::path(url);

    auto path = u_path.filename();

    if (fs::exists(path)) {
        BOOST_LOG_TRIVIAL(debug) << "file " << path << " exists.";
        return read_file(path);
    }

    CURL *curl_handle;
    CURLcode res;

    string chunk;

    curl_global_init(CURL_GLOBAL_ALL);

    BOOST_LOG_TRIVIAL(trace) << "initializing curl handle";
    curl_handle = curl_easy_init();


    curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &chunk);
    curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");

    // added options that may be required
    curl_easy_setopt(curl_handle, CURLOPT_FOLLOWLOCATION, 1L);  // redirects
    curl_easy_setopt(curl_handle, CURLOPT_HTTPPROXYTUNNEL, 1L); // corp. proxies etc.
//    curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1L); // we want it all
    // curl_easy_setopt(curl_handle, CURLOPT_REDIR_PROTOCOLS, CURLPROTO_HTTP | CURLPROTO_HTTPS);

    BOOST_LOG_TRIVIAL(trace) << "performing the request";

    res = curl_easy_perform(curl_handle);

    BOOST_LOG_TRIVIAL(trace) << "request performed.";

    if (res != CURLE_OK) {
        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << '\n';
    } else {
        write_file(path, chunk);
        std::cout << chunk.size() << " bytes retrieved\n";
    }

    curl_easy_cleanup(curl_handle);
    curl_global_cleanup();

    return string_to_vector(chunk);
}
