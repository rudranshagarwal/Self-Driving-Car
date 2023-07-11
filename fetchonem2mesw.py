
import matplotlib.pyplot as plt
import requests
c = []

uri_cnt = "http://esw-onem2m.iiit.ac.in:443/~/in-cse/in-name/Team-24/Node-1/Data/la"


header = {
'X-M2M-Origin': 'KX#XtZ:29kxeL',
'Content-type': 'application/json'
}
response = requests.get(uri_cnt, headers=header)
data = response.json()

# print(data)
# data = data["m2m:cnt"]

# data = data["m2m:cnt"]


# data = data["m2m:cnt"]

# data = data["m2m:cnt"]

# print(data)


# Ion
# print(data)

data = data["m2m:cin"]["con"]

print(data)


# x = []
# y = []
# t = []

# x.append(0)
# y.append(0)
 
# c = 0
# for i in data:
#     print("Hi")
#     print(i)
#     if(c>=0):
#         ans = (i["con"])
#         a = ans.split()
#         x.append(float(a[0]))
#         y.append(float(a[1]))
#         t.append(float(a[2]))
#     c = c + 1
# print(x)
# print(y)

 



# plt.plot(x, y)
# plt.xlabel('x coordinate')
# plt.ylabel('y coordinate')
# plt.title('path')
# plt.show()
# print(response.text)
# print(type(response))

# print(max(ans))
# print(ans.index(max(ans)))
# print(max(c))
# print(c.index(max(c)))

