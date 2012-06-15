#include "formatting.h"
#include "client.h"

static int main(int argc, char** argv) {
  xmlrpc_limit_set(XMLRPC_XML_SIZE_LIMIT_ID, 5e6);
}
