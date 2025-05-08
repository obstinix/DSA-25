n = int(input("Enter the number of elements of Set A : "))
SetA = set()
for i in range(n):
    ele = int(input("Enter element : "))
    SetA.add(ele)
print("Set A : ",SetA)

#insert element
ele1 = int(input("Enter element to insert : "))
SetA.add(ele1)
print("Set A after inserting ",ele1," ",SetA)

#remove element
ele2 = int(input("Enter element to remove : "))
SetA.remove(ele2)
print("Set A after inserting ",ele2," ",SetA)

#Search element
ele3 = int(input("Enter element to search : "))
if ele3 in SetA :
    print("Element is in set.")
else :
    print("Element is not in set.")

#Size
print("Size of Set A is ",len(SetA))

m = int(input("Enter no. of elements in Set B : "))
SetB = set()
for i in range(m) :
    ele4 = int(input("Enter element : "))
    SetB.add(ele4)
print("Set B : ",SetB)

SetC = SetA.union(SetB)
print("Union of Set A & Set B is ",SetC)

SetD = SetA.intersection(SetB)
print("Intersection of Set A & Set B is ",SetD)

SetE = SetA.difference(SetB)
print("Difference of Set A & Set B is ",SetE)
