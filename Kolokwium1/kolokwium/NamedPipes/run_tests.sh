run_test 100 "Short message" "small buffer and short message"
run_test 1024 "Short message" "large buffer and short message"
run_test 10 "This is a very long message that exceeds the buffer size to test partial reads and writes." "small buffer and long message"
run_test 34 "Exactly thirty-four characters!" "buffer size exactly matching message length"
run_test 1 "Msg" "extremely small buffer size"
run_test 50 "This should not fail" "normal length message"

# Test with non-numeric buffer size
run_test "abc" "This should fail" "non-numeric buffer size (should handle error)"

# Clean up
rm -f $FIFO_PATH
