// Stand-alone binary to load up a FAR and rewrite some strings.

#include <fst/compat.h>
#include <thrax/compat/compat.h>
#include <../bin/rewrite-tester-utils.h>

int main(int argc, char **argv) {
  std::set_new_handler(FailedNewHandler);
  SET_FLAGS(argv[0], &argc, &argv, true);

  std::unique_ptr<RewriteTesterUtils> utils(new RewriteTesterUtils());
  utils->Initialize();
  utils->Run();

  return 0;
}
