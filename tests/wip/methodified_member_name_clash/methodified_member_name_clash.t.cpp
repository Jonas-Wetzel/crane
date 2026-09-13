#include <methodified_member_name_clash.h>

#include <cstdio>

int main() {
  MethodifiedMemberNameClash::wrap w =
      MethodifiedMemberNameClash::wrap::w(MethodifiedMemberNameClash::other::o1());
  std::printf("%llu %llu\n", (unsigned long long)w.v(),
              (unsigned long long)w.variant_t());
  return 0;
}
