import matplotlib.pyplot as plt
import subprocess


method = '0'
a = '1.010000'
x0 = '0.000000'
t0 = '0.000000'
dt = '0.005000'
n = '10000'

path_to_files_folder = "[PATH TO FOLDER]\\results\\"
path_to_img_folder = "[PATH TO FOLDER]\\figures\\"
path_to_exe = '[PATH TO .EXE FILE]'

methods = {'0':'Euler'}
args = [path_to_exe, method, a, x0, t0, dt, n]
pr = subprocess.Popen(args)
pr.wait()

tr1 = []
tr2 = []
file_name = path_to_files_folder + methods[method] + '_n' + n + '_dt' + dt + '_a' + a + '.txt'
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

plt.title(methods[method] + ', a = ' + a + ', n = ' + n + ', dt =' + dt)
plt.legend(['x','x\''])
plt.ylabel('x, x\'')
plt.xlabel('ti')
#plt.show()
plt.savefig(path_to_img_folder + methods[method] + '_n' + n + '_dt' + dt + '_a' + a + ".png")