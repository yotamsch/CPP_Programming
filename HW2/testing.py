import subprocess

# The local folder in which the tests are in
prefix = "./hw1_tests"
# NOTE: The tests are each in a subfolder named 'test_#'
#       where # is the test number.

# The mode to check, file-vs-file, file-vs-auto, auto-vs-file
mode = "file-vs-file"

out_path = "%s/rps.output" % (prefix)
suffix_p1 = "player1.rps_board"
suffix_p2 = "player2.rps_board"
suffix_m1 = "player1.rps_moves"
suffix_m2 = "player2.rps_moves"

t_res = "%s/results.txt" % (prefix)
t_exp = "%s/expected.txt" % (prefix)
f_res = open(t_res, "w")
f_exp = open(t_exp, "w")

for i in range(0,23):
    s1 = "%s/test_%d/%s" % (prefix, i, suffix_p1)
    s2 = "%s/test_%d/%s" % (prefix, i, suffix_p2)
    s3 = "%s/test_%d/%s" % (prefix, i, suffix_m1)
    s4 = "%s/test_%d/%s" % (prefix, i, suffix_m2)
    s_orig = "%s/test_%d/rps.expected" % (prefix, i)
    action = ["./ex2", mode, out_path, s1, s2, s3, s4]
    print("\nTest %d:\n\t%s" % (i, action))
    code = subprocess.call(action)
    if code == 1:
        continue
    f_out = open(out_path,"r")
    lines_out = f_out.readlines()
    f_orig = open(s_orig, "r")
    lines_expected = f_orig.readlines()
    f_res.write("\ntest_ %d\n-----------\n" % i)
    f_exp.write("\ntest_ %d\n-----------\n" % i)
    f_res.writelines(lines_out)
    f_exp.writelines(lines_expected)

### TALA ###
for i in range(2,21):
    if i==12:
        # why?
        continue
    s1 = "%s/case%d/%s" % (prefix, i, suffix_p1)
    s2 = "%s/case%d/%s" % (prefix, i, suffix_p2)
    s3 = "%s/case%d/%s" % (prefix, i, suffix_m1)
    s4 = "%s/case%d/%s" % (prefix, i, suffix_m2)
    s_orig = "%s/case%d/rps.expected" % (prefix, i)
    action = ["./ex2", mode, out_path, s1, s2, s3, s4]
    print("\ncase %d:\n\t%s" % (i, action))
    code = subprocess.call(action)
    if code == 1:
        continue
    f_out = open(out_path,"r")
    lines_out = f_out.readlines()
    f_orig = open(s_orig, "r")
    lines_expected = f_orig.readlines()
    f_res.write("\ncase %d\n-----------\n" % i)
    f_exp.write("\ncase %d\n-----------\n" % i)
    f_res.writelines(lines_out)
    f_exp.writelines(lines_expected)
############

f_res.write("\n- End -")
f_exp.write("\n- End -")
