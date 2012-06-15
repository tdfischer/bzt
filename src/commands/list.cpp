#include "list.h"
#include "../client.h"
#include "../formatting.h"
#include "../configuration.h"

static gchar* bzProduct = NULL;

static GOptionEntry entries[] = 
{
  { "product", 'p', 0, G_OPTION_ARG_STRING, &bzProduct, "Bugzilla product", NULL },
  { NULL }
};

GOptionGroup *TaskList::options() const
{
  GOptionGroup *group = g_option_group_new("list", "List tasks", "List tasks", NULL, NULL);
  g_option_group_add_entries(group, entries);
  return group;
}

int TaskList::exec(std::vector<std::string> args)
{
  std::string product;
  Configuration config;
  if (bzProduct == NULL)
    product = config.getString("product");
  else
    product = bzProduct;
  Client c(config.getString("url"));
  std::vector<Bug> bugs;
  std::vector<Bug>::iterator it;
  bzSearch search;
  search.addField("severity", xmlrpc_c::value_string(config.getString("severity", "task")));
  if (!product.empty())
    search.addField("product", xmlrpc_c::value_string(product));
  bugs = c.search(search);
  for(it = bugs.begin();it != bugs.end();it++) {
    printBugTree(*it);
  }
  return 0;
}
