import subprocess

prefix = "./testsTala/"
suffix_p1 = "/player1.rps_board"
suffix_p2 = "/player2.rps_board"
suffix_m1 = "/player1.rps_moves"
suffix_m2 = "/player2.rps_moves"

t_output = "./test_result.txt"
f_o = open(t_output, "w")
f_o.write("Testing Results:\n\n")

for i in range(1,18):
    s1 = "%scase%d%s" % (prefix, i, suffix_p1)
    s2 = "%scase%d%s" % (prefix, i, suffix_p2)
    s3 = "%scase%d%s" % (prefix, i, suffix_m1)
    s4 = "%scase%d%s" % (prefix, i, suffix_m2)
    action = ["./ex1", s1, s2, s3, s4]
    print("Testing: CASE %d" % (i))
    code = subprocess.call(action)
    if code == 1:
        continue
    f = open("./rps.output","r")
    lines = f.readlines()
    f_o.write("case %d\n-----------\n" % i)
    f_o.writelines(lines)


f_o.write("\nEnd Testing")
