// Feature tests of parsing new Checked C bounds declarations.
//
// The following lines are for the LLVM test harness:
//
// RUN: %clang_cc1 -verify -fcheckedc-extension %s

extern void f1(array_ptr<int> arr : count(5)) {
}

extern void f2(array_ptr<int> arr : count(3 + 2)) {
}

extern void f3(int len, array_ptr<int> arr : count(len)) {
}

extern void f3a(array_ptr<int> arr : count(len), int len) {
}

extern void f4(array_ptr<int> arr : byte_count(20)) {
}

extern void f5(array_ptr<int> arr : byte_count(5 * sizeof(int))) {
}

extern void f6(array_ptr<int> arr : bounds(arr, arr + 5)) {
}

extern void f7(int start, array_ptr<int> midarr : 
               bounds(midarr - start, midarr - start + 5)) {
}

extern void f7a(array_ptr<int> midarr :
   bounds(midarr - start, midarr - start + 5), int start) {
}

extern void f8(array_ptr<int> arr : bounds(none)) {
}

// count is a contextual keyword.  It is only a keyword when it
// immediately follows the ':' in a bounds declaration.
extern void f9(int count, array_ptr<int> arr : count(count)) {
}

extern void f9a(array_ptr<int> arr : count(count), int count) {
}

// none is a contextual keyword.  It is only a keyword when it
// immediately follows the ':' in a bounds declaration.
extern void f10(int none, array_ptr<int> arr : count(none)) {
}

extern void f10a(array_ptr<int> arr : count(none), int none) {
}

// bounds is a contextual keyword.  It is only a keyword when it
// immediately follows the ':' in a bounds declaration.
extern void f11(int bounds, array_ptr<int> arr : bounds(arr, arr + 5)) {
}

extern void f11a(array_ptr<int> arr : bounds(arr, arr + 5), int bounds) {
}

extern void f12(array_ptr<int> lower, array_ptr<int> upper, 
                array_ptr<int> arr : bounds(lower, upper)) {
}

extern void f12a(array_ptr<int> arr : bounds(lower, upper),
                 array_ptr<int> lower, array_ptr<int> upper) {
}

// The first parameter will have bounds(lower, upper)
extern void f13(array_ptr<int> arr : bounds(lower, upper),
                array_ptr<int> lower, array_ptr<int> upper) {
}

extern void f14(array_ptr<int> arr : 6 + 6) { // expected-error {{expected bounds expression}}
}

extern void f15(array_ptr<int> arr : 6 + 6, array_ptr<int> arr2 : count(5)) { // expected-error {{expected bounds expression}}
}

//
// Parsing of more complicated parameter declarators with bounds declarations
// 

// Incomplete array types with bounds declarations
extern void f16(int arr checked[] : count(5)) {
}

extern void f17(int arr checked[] : count(3 + 2)) {
}

extern void f18(int len, int arr checked[] : count(len)) {
}

extern void f18a(int arr checked[] : count(len), int len) {
}

// declare arrays of pointers to integers with bounds declarations
extern void f19(int *arr checked[] : count(5)) {
}

extern void f20(int *arr checked[] : count(3 + 2)) {
}

extern void f21(int len, int *arr checked[] : count(len)) {
}

extern void f21a(int *arr checked[] : count(len), int len) {
}

// Checked array of pointers to functions.   Note that this shows a potential
// ambiguity in the grammar. We have to parenthesize the inner declarator
// to avoid : count(len) being parsed as part of the type of arr, not a bounds
// expression.
extern void f22(int len, int ((*arr checked[])(int, int)) : count(len)) {
}

extern void f22a(int((*arr checked[])(int, int)) : count(len), int len) {
}

// checked array of pointers to functions
extern void f23(int len, int ((*arr checked[])(int, int)) : bounds(arr, arr + len)) {
}

extern void f23a(int((*arr checked[])(int, int)) : bounds(arr, arr + len), int len) {
}

extern void f24(int arr : count(len)) { // expected-error {{use of undeclared identifier 'len'}}
}

// check parsing of a function with lots of arguments.
extern void f25(int a, int b, int c, int d, float f, int g, int h, int i,
                int j, int k, int len, int arr : count(len)) {
}

// intentionally misspell bounds to cause a parsing error.
extern void f26(int len,
                int arr : boounds(arr, arr + len)) { // expected-error {{expected bounds expression}}
}

extern void f27(int len,
                int arr : boounds(arr, arr + len), // expected-error {{expected bounds expression}}
                int flag) {
}

// intentionally misspell count to cause a parsing error.
extern void f28(int len,
                int arr : coount(len)) { // expected-error {{expected bounds expression}}
}

extern void f29(int len,
                int arr : coount(len), // expected-error {{expected bounds expression}}
                int flag) {
}

//  bounds expressions with parenthesized subexpressions
extern void f30(int len,
                int arr : bounds(arr, (arr + len))) {
}

extern void f31(int len,
                int arr : bounds((arr + len - (len)), (arr + len))) {
}


extern void f32(int len,
                int arr : count((len)),
                int flag) {
}
