n = int(input("Enter no. of Telephone Numbers : "))
HT = [0] * n
print("\n*** Initial Hashtable ***")
print(HT)
print("Insert keys using linear probing")
for i in range(len(HT)) :
    key = int(input("Enter a telephone number : "))
    ind = key % n 
    if HT[ind]==0:
        HT[ind] = key
    else :
        ind = (key+1)%n
        if HT[ind] == 0 :
            HT[ind] = key
        break

print("\n***** Hash Table after insertion *****")
print(HT)

print("Insert keys using collision resolution")
for i in range(len(HT)):
    key= int(input("Enter a telephone number : "))
    ind= key % len(HT)
    if HT[ind] == 0 :
        HT[ind] = key;
    else:
        occ_key = HT[ind]
        occ_ind = occ_key % len(HT)
        if occ_ind != ind :
            HT[ind]=key 
        else :
            for j in range(len(HT)):
                ind = (key + 1) % len(HT)
                if HT[ind] == 0 :
                    HT[ind]=key 
                break

print("***** Hash Table after collision resolution *****")
print(HT)

print("Insert keys using Quadratic probing")
for i in range(len(HT)) :
    key = int(input("Enter a telephone number : "))
    ind = key % n 
    if HT[ind]==0:
        HT[ind] = key
    else :
        for j in range(len(HT)):    
            indn = (key+ j*j)%n
            if HT[indn] == 0 :
             HT[indn] = key
    
print("***** Hash Table after Quadratic probing *****")
print(HT)


