#include "SmtpSrv.h"
#include "HttpSrv.h"

using namespace std;

int main(int argc, char** argv) {

    HttpSrv httpSrv;
    httpSrv.run(argc, argv);
	
}