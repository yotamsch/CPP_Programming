import subprocess

# The local folder in which the tests are in
prefix = "./hw1_tests"
# NOTE: The tests are each in a subfolder named 'test_#'
#       where # is the test number.

suffix_p1 = "player1.rps_board"
suffix_p2 = "player2.rps_board"
suffix_m1 = "player1.rps_moves"
suffix_m2 = "player2.rps_moves"

for i in range(2,21):
    s1 = "%s/case%d/%s" % (prefix, i, suffix_p1)
    s2 = "%s/case%d/%s" % (prefix, i, suffix_p2)
    s3 = "%s/case%d/%s" % (prefix, i, suffix_m1)
    s4 = "%s/case%d/%s" % (prefix, i, suffix_m2)
    out_path = "%s/case%d/rps.expected" % (prefix,i)
    action = ["./ex1", out_path, s1, s2, s3, s4]
    print("\nCase %d:\n\t%s" % (i, action))
    code = subprocess.call(action)
    if code == 1:
        continue
