#include "loopify_gap_ackermann.h"

uint64_t
LoopifyGapAckermann::ack(uint64_t m,
                         uint64_t x0_) { /// _Enter: captures varying parameters
                                         /// for each recursive call.

  struct _Enter {
    uint64_t x0_;
    uint64_t m;
  };

  using _Frame = std::variant<_Enter>;
  uint64_t _result{};
  crane::small_vector<_Frame> _stack;
  _stack.emplace_back(_Enter{x0_, m});
  /// Loopified ack: _Enter.
  while (!_stack.empty()) {
    _Frame _frame = std::move(_stack.back());
    _stack.pop_back();
    auto _f = std::move(std::get<_Enter>(_frame));
    uint64_t x0_ = _f.x0_;
    uint64_t m = _f.m;
    auto ack_n_impl = [&](auto &, uint64_t n) -> uint64_t {
      /// _Enter: captures varying parameters for each recursive call.
      struct _Enter {
        uint64_t n;
      };
      /// _Resume_n_: saves [m_], resumes after recursive call with _result.
      struct _Resume_n_ {
        uint64_t m_;
      };
      using _Frame = std::variant<_Enter, _Resume_n_>;
      uint64_t _result{};
      crane::small_vector<_Frame> _stack;
      _stack.emplace_back(_Enter{n});
      /// Loopified ack_n: _Enter -> _Resume_n_.
      while (!_stack.empty()) {
        _Frame _frame = std::move(_stack.back());
        _stack.pop_back();
        if (std::holds_alternative<_Enter>(_frame)) {
          auto _f = std::move(std::get<_Enter>(_frame));
          uint64_t n = _f.n;
          if (m <= 0) {
            _result = (n + 1);
          } else {
            uint64_t m_ = m - 1;
            if (n <= 0) {
              _result = ack(m_, UINT64_C(1));
            } else {
              uint64_t n_ = n - 1;
              _stack.emplace_back(_Resume_n_{m_});
              _stack.emplace_back(_Enter{n_});
            }
          }
        } else {
          auto _f = std::move(std::get<_Resume_n_>(_frame));
          _result = ack(_f.m_, std::move(_result));
        }
      }
      return _result;
    };
    auto ack_n = [&](uint64_t n) -> uint64_t {
      return ack_n_impl(ack_n_impl, n);
    };
    _result = ack_n(x0_);
  }
  return _result;
}
