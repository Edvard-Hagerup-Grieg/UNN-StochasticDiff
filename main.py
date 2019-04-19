import matplotlib.pyplot as plt
import numpy as np
import subprocess
import threading
import time
import os


method = '2'
a = '0.500000'
x0 = '0.000000'
t0 = '0.000000'
dt = '0.005000'
n = '600000'
D = '0.300000'

path_to_files_folder = "C:\\Users\\Franz\\Desktop\\GitHub\\UNN-StochasticDiff\\results\\"
path_to_img_folder = "C:\\Users\\Franz\\Desktop\\GitHub\\UNN-StochasticDiff\\figures\\"
path_to_exe = 'C:\\Users\\Franz\\Desktop\\GitHub\\UNN-StochasticDiff\\StochasticDiff\\Release\\StochasticDiff.exe'

methods = {'0':'Euler', '1':'Heun', '2':'Jump_mean'}

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

    fig = plt.figure()
    ax = plt.gca()

    ax.plot(range(int(n)), tr1, color = 'blue')
    ax.plot(range(int(n)), tr2, color = 'red')

    plt.title(methods[method] + ', a = ' + a + ', n = ' + n + ', dt =' + dt + ', D =' + D)
    plt.legend(['x','x\''])
    plt.ylabel('x, x\'')
    plt.xlabel('ti')
    plt.show()
    #plt.savefig(path_to_img_folder + methods[method] + '_n' + n + '_dt' + dt + '_a' + a + '_D' + D + ".png")

def run_jump_experiment():
    Tr1 = []
    Tr2 = []
    Jump = []
    file_name = path_to_files_folder + methods[method] + '_n' + n + '_dt' + dt + '_a' + a + '_D' + D + '.txt'
    f = open(file_name, 'r')
    data = f.read().split("\n")

    iter = 100
    for i in range(iter):
        print("ITER: ", i)
        tr1 = []
        tr2 = []
        jump = []
        for j in range(int(n)):
            x, xt, jm = data[i*int(n) + j].split(" ")
            tr1.append(float(x))
            tr2.append(float(xt))
            jump.append(int(jm))

        Tr1.append(tr1)
        Tr2.append(tr2)
        Jump.append(jump)

    Tr1 = np.array(Tr1)
    Tr2 = np.array(Tr2)
    Jump = np.array(Jump)

    x = []
    xt = []
    Pr = []
    for i in range(Tr1.shape[1]):
        x.append(np.mean(Tr1[:,i]))
        xt.append(np.mean(Tr2[:,i]))
        Pr.append(sum(Jump[:,i]) / iter)


    fig = plt.figure()
    ax = plt.gca()

    ax.plot(range(int(n)), x, color = 'blue')
    # ax.plot(range(int(n)), xt, color = 'red')

    plt.title(methods[method] + ', a = ' + a + ', n = ' + n + ', dt =' + dt + ', D =' + D)
    plt.legend(['x','x\''])
    plt.ylabel('x, x\'')
    plt.xlabel('ti')

    fig2 = plt.figure()
    ax2 = plt.gca()

    ax2.plot(range(int(n)), Pr, color='blue')

    plt.title(methods[method] + ', a = ' + a + ', n = ' + n + ', dt =' + dt + ', D =' + D)
    plt.legend(['Pr(jump)'])
    plt.ylabel('Pr')
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
    # plt.legend(['Pr(jump)'])
    plt.ylabel('1 - Pr(jump)')
    plt.xlabel('ti')

    plt.show()
    # plt.savefig(path_to_img_folder + methods[method] + '_n' + n + '_dt' + dt + '_a' + a + '_D' + D + ".png")


if __name__ == "__main__":
    # run_exe()
    # visual()
    # run_jump_experiment()
    run_jump_mean_experiment()