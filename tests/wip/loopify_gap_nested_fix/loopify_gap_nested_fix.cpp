#include "loopify_gap_nested_fix.h"

uint64_t LoopifyGapNestedFix::rose_sum(
    const LoopifyGapNestedFix::rose
        &r) { /// _Enter: captures varying parameters for each recursive call.

  struct _Enter {
    LoopifyGapNestedFix::rose r;
  };

  using _Frame = std::variant<_Enter>;
  uint64_t _result{};
  crane::small_vector<_Frame> _stack;
  _stack.emplace_back(_Enter{r});
  /// Loopified rose_sum: _Enter.
  while (!_stack.empty()) {
    _Frame _frame = std::move(_stack.back());
    _stack.pop_back();
    auto _f = std::move(std::get<_Enter>(_frame));
    const LoopifyGapNestedFix::rose &r = std::move(_f.r);
    const auto &[a0, a1] =
        std::get<typename LoopifyGapNestedFix::rose::Rose0>(r.v());
    auto sum_list_impl =
        [&](auto &, const List<LoopifyGapNestedFix::rose> &l) -> uint64_t {
      /// _Enter: captures varying parameters for each recursive call.
      struct _Enter {
        const List<LoopifyGapNestedFix::rose> *l;
      };
      /// _Resume_Cons: saves [a2], resumes after recursive call with _result.
      struct _Resume_Cons {
        uint64_t a2;
      };
      using _Frame = std::variant<_Enter, _Resume_Cons>;
      uint64_t _result{};
      crane::small_vector<_Frame> _stack;
      _stack.emplace_back(_Enter{&l});
      /// Loopified sum_list: _Enter -> _Resume_Cons.
      while (!_stack.empty()) {
        _Frame _frame = std::move(_stack.back());
        _stack.pop_back();
        if (std::holds_alternative<_Enter>(_frame)) {
          auto _f = std::move(std::get<_Enter>(_frame));
          const List<LoopifyGapNestedFix::rose> &l = *_f.l;
          if (std::holds_alternative<
                  typename List<LoopifyGapNestedFix::rose>::Nil>(l.v())) {
            _result = UINT64_C(0);
          } else {
            const auto &[a2, a3] =
                std::get<typename List<LoopifyGapNestedFix::rose>::Cons>(l.v());
            _stack.emplace_back(_Resume_Cons{rose_sum(a2)});
            _stack.emplace_back(_Enter{crane_raw(a3)});
          }
        } else {
          auto _f = std::move(std::get<_Resume_Cons>(_frame));
          _result = (_f.a2 + std::move(_result));
        }
      }
      return _result;
    };
    auto sum_list = [&](const List<LoopifyGapNestedFix::rose> &l) -> uint64_t {
      return sum_list_impl(sum_list_impl, l);
    };
    _result = (a0 + sum_list(*a1));
  }
  return _result;
}

uint64_t LoopifyGapNestedFix::rose_sum_sample(std::monostate) {
  return rose_sum(sample_tree);
}
