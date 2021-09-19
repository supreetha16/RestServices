// CivetWeb_Example2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/*#include <iostream>

int main()
{
    std::cout << "Hello World!\n";
}
*/
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

/*
* Copyright (c) 2013 No Face Press, LLC
* License http://opensource.org/licenses/mit-license.php MIT License
*/

// Simple example program on how to use Embedded C interface.
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <string.h>
#include "civetweb.h"



#define DOCUMENT_ROOT "."
#define PORT "8888"
#define EXAMPLE_URI "/example"
#define EXIT_URI "/exit"
int exitNow = 0;

int ExampleHandler(struct mg_connection* conn, void* cbdata)
{
    mg_printf(conn, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
    mg_printf(conn, "<html><body>");
    mg_printf(conn, "<h2>This is an example text from a C handler</h2>");
    mg_printf(conn, "<p>To see a page from the A handler <a href=\"A\">click here</a></p>");
    mg_printf(conn, "<p>To see a page from the A/B handler <a href=\"A/B\">click here</a></p>");
    mg_printf(conn, "<p>To see a page from the *.foo handler <a href=\"xy.foo\">click here</a></p>");
    mg_printf(conn, "<p>To exit <a href=\"%s\">click here</a></p>",
        EXIT_URI);
    mg_printf(conn, "</body></html>\n");
        return 1;
}

int ExitHandler(struct mg_connection* conn, void* cbdata)
{
    mg_printf(conn, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n");
    mg_printf(conn, "Bye!\n");
    exitNow = 1;
    return 1;
}

int AHandler(struct mg_connection* conn, void* cbdata)
{
    mg_printf(conn, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
    mg_printf(conn, "<html><body>");
    mg_printf(conn, "<h2>This is the A handler!!!</h2>");
    mg_printf(conn, "</body></html>\n");
    return 1;
}

int ABHandler(struct mg_connection* conn, void* cbdata)
{
    mg_printf(conn, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
    mg_printf(conn, "<html><body>");
    mg_printf(conn, "<h2>This is the AB handler!!!</h2>");
    mg_printf(conn, "</body></html>\n");
    return 1;
}

int FooHandler(struct mg_connection* conn, void* cbdata)
{
    /* Handler may access the request info using mg_get_request_info */
    const struct mg_request_info* req_info = mg_get_request_info(conn);

    mg_printf(conn, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
    mg_printf(conn, "<html><body>");
    mg_printf(conn, "<h2>This is the Foo handler!!!</h2>");
    mg_printf(conn, "<p>The request was:<br><pre>%s %s HTTP/%s</pre></p>",
        req_info->request_method, req_info->local_uri, req_info->http_version);
    mg_printf(conn, "</body></html>\n");
    return 1;
}


int main(int argc, char* argv[])
{

    const char* options[] = { "document_root", DOCUMENT_ROOT,
                               "listening_ports", PORT, 0
    };
    struct mg_callbacks callbacks;
    struct mg_context* ctx;

    memset(&callbacks, 0, sizeof(callbacks));
    ctx = mg_start(&callbacks, 0, options);

    mg_set_request_handler(ctx, EXAMPLE_URI, ExampleHandler, 0);
    mg_set_request_handler(ctx, EXIT_URI, ExitHandler, 0);
    mg_set_request_handler(ctx, "/a", AHandler, 0);
    mg_set_request_handler(ctx, "/a/b", ABHandler, 0);
    mg_set_request_handler(ctx, "**.foo$", FooHandler, 0);

    printf("Browse files at http://localhost:%s/\n", PORT);
    printf("Run example at http://localhost:%s%s\n", PORT, EXAMPLE_URI);
    printf("Exit at http://localhost:%s%s\n", PORT, EXIT_URI);

    while (!exitNow) {
#ifdef _WIN32
        Sleep(1000);
#else
        sleep(1);
#endif
    }

    printf("Bye!\n");

    return 0;
}