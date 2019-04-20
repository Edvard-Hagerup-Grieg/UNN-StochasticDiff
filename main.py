import matplotlib.pyplot as plt
import numpy as np
import subprocess

run_id = 2
'''
0: run .exe file
1: plot x(t) and x'(t)
2: plot Pr(t)
3: plot tau(D)
'''

method = '2'
'''
'0': 'Euler'
'1': 'Heun'
'2': 'Jump'
'''

a = '0.500000'
x0 = '0.000000'
t0 = '0.000000'
dt = '0.050000'
n = '40000'
D = '1.000000'

path_to_files_folder = "[PATH TO FOLDER]\\results\\"
path_to_img_folder = "[PATH TO FOLDER]\\figures\\"
path_to_exe = '[PATH TO .EXE FILE]\\StochasticDiff.exe'

methods = {'0':'Euler', '1':'Heun', '2':'Jump'}

def run_exe():
    args = [path_to_exe, method, a, x0, t0, dt, n, D]
    pr = subprocess.Popen(args, stdout=subprocess.PIPE, shell=True)
    print("Time(sec): ", pr.communicate()[0].decode('utf-8'))

def visual():
    tr1 = []
    tr2 = []
    file_name = path_to_files_folder + methods[method] + '_n' + n + '_dt' + dt + '_a' + a + '_D' + D + '.txt'
    f = open(file_name, 'r')
    data = f.read().split("\n")
    for d in data[:-1]:
        x, xt = d.split(" ")
        tr1.append(float(x))
        tr2.append(float(xt))

    plt.figure()
    ax = plt.gca()

    ax.plot(range(int(n)), tr1, color = 'blue')
    ax.plot(range(int(n)), tr2, color = 'red')

    plt.title(methods[method] + ', a = ' + a + ', n = ' + n + ', dt =' + dt + ', D =' + D)
    plt.legend(['x','x\''])
    plt.ylabel('x, x\'')
    plt.xlabel('ti')

    plt.show()
    #plt.savefig(path_to_img_folder + methods[method] + '_n' + n + '_dt' + dt + '_a' + a + '_D' + D + ".png")

def run_jump_mean_experiment():
    file_name = path_to_files_folder + methods[method] + '_n' + n + '_dt' + dt + '_a' + a + '_D' + D + '.txt'
    f = open(file_name, 'r')
    Pr = f.read().split("\n")

    new_Pr = []
    for pr in Pr[:-1]:
        new_Pr.append(float(pr))

    Pr = np.array(new_Pr)

    plt.figure()
    plt.plot(np.arange(len(Pr)), Pr, color='blue')

    plt.title(methods[method] + ', a = ' + a + ', n = ' + n + ', dt =' + dt + ', D =' + D)
    plt.ylabel('1 - Pr(jump)')
    plt.xlabel('ti')

    plt.show()
    # plt.savefig(path_to_img_folder + methods[method] + '_n' + n + '_dt' + dt + '_a' + a + '_D' + D + ".png")

def run_tau_experiment():
    list = ['0.' + str(i) + '00000' for i in range(10)] + \
           ['1.' + str(i) + '00000' for i in range(10)] + \
           ['2.' + str(i) + '00000' for i in range(10)] + \
           ['3.' + str(i) + '00000' for i in range(10)] + \
           ['4.' + str(i) + '00000' for i in range(10)] + \
           ['5.' + str(i) + '00000' for i in range(10)] + \
           ['6.' + str(i) + '00000' for i in range(10)] + \
           ['7.' + str(i) + '00000' for i in range(10)] + \
           ['8.' + str(i) + '00000' for i in range(1)]

    I = []
    for d in list:
        file_name = path_to_files_folder + methods[method] + '_n' + n + '_dt' + dt + '_a' + a + '_D' + d + '.txt'
        f = open(file_name, 'r')
        Pr = f.read().split("\n")

        pr0 = float(Pr[0])
        pr1 = float(Pr[-2])
        sum = (pr0 + pr1) / 2.0
        for pr in Pr[:-2]:
            sum += float(pr)

        I.append(sum * 0.1)

#        if d == list[0]:
 #           plt.subplot(2, 1, 1)
  #          plt.plot(np.arange(len(Pr)), Pr, color='blue')
#
 #           plt.title('D =' + d)
  #          plt.ylabel('1 - Pr(jump)')
   #         plt.xlabel('ti')
#
 #       if d == list[-1]:
  #          plt.subplot(2, 1, 2)
   #         plt.plot(np.arange(len(Pr)), Pr, color='blue')
#
 #           plt.title('D =' + d)
  #          plt.ylabel('1 - Pr(jump)')
   #         plt.xlabel('ti')

    plt.plot(np.arange(0.0, 8.1, 0.1), I)
    plt.show()
    # plt.savefig(path_to_img_folder + methods[method] + '_n' + n + '_dt' + dt + '_a' + a + '_D' + D + ".png")



if __name__ == "__main__":
    if run_id == 0: run_exe()
    if run_id == 1: visual()
    if run_id == 2: run_jump_mean_experiment()
    if run_id == 3: run_tau_experiment()