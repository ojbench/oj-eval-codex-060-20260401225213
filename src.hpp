// Chainable validator implementation for "expect" API.
// Only <vector> may be included per problem constraints.
#include <vector>

// We avoid using namespace std; and rely on ADL and std:: qualifiers.

template <typename T>
class Expect {
 public:
  explicit Expect(const T& value) : x(value), not_flag(false), ok(true) {}

  // Flip the negation flag for subsequent checks.
  Expect& Not() {
    not_flag = !not_flag;
    return *this;
  }

  // x == y
  Expect& toBe(const T& y) {
    if (ok) {
      bool res = (x == y);
      ok = apply(res);
    }
    return *this;
  }

  // x in y (vector)
  Expect& toBeOneOf(const std::vector<T>& y) {
    if (ok) {
      bool found = false;
      for (const auto& z : y) {
        if (x == z) { found = true; break; }
      }
      ok = apply(found);
    }
    return *this;
  }

  // x <= y
  Expect& le(const T& y) {
    if (ok) {
      bool res = !(y < x); // use only < to support custom types
      ok = apply(res);
    }
    return *this;
  }

  // x >= y
  Expect& ge(const T& y) {
    if (ok) {
      bool res = !(x < y); // use only < to support custom types
      ok = apply(res);
    }
    return *this;
  }

  // x < y
  Expect& lt(const T& y) {
    if (ok) {
      bool res = (x < y);
      ok = apply(res);
    }
    return *this;
  }

  // x > y
  Expect& gt(const T& y) {
    if (ok) {
      bool res = (y < x); // use only < to support custom types
      ok = apply(res);
    }
    return *this;
  }

  // Implicit conversion to bool for if(...) contexts.
  operator bool() const { return ok; }

 private:
  T x;
  bool not_flag;
  bool ok;

  bool apply(bool res) {
    if (not_flag) res = !res;
    // chain is AND of all conditions
    return ok && res;
  }
};

template <typename T>
Expect<T> expect(const T& value) {
  return Expect<T>(value);
}

