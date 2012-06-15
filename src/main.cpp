#include <iostream>
#include "command.h"
#include <xmlrpc-c/base.h>

int main(int argc, char** argv) {
  GError *error = NULL;
  GOptionContext *context;
  GOptionGroup *commandGroup;
  Command *cmd;
  xmlrpc_limit_set(XMLRPC_XML_SIZE_LIMIT_ID, 5e6);

  context = g_option_context_new(" - Bugzilla Task Tool");
  if (argc >= 3)
    g_option_context_set_help_enabled(context, false);
  g_option_context_parse(context, &argc, &argv, &error);
  g_option_context_set_help_enabled(context, true);

  cmd = Command::loadCommand(argv[1]);
  if (!cmd) {
    g_print("%s is not a bzt command.\n", argv[1]);
    return 1;
  }
  commandGroup = cmd->options();
  if (commandGroup) {
    g_option_context_add_group(context, commandGroup);
    g_option_context_set_main_group(context, commandGroup);
  }

  // Now re-parse things with the command loaded
  if (!g_option_context_parse(context, &argc, &argv, &error)) {
    g_print("Bad option: %s\n", error->message);
    exit(1);
  }

  std::vector<std::string> args;
  for(int i = 2;i<argc;i++) {
    args.push_back(argv[i]);
  }
  return cmd->exec(args);
}
