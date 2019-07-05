import package.xlsxInput as xlsxInput
import package.messCSVdata as messData

print('by @rtb!ndu')
print("plese store your '.xlsx' file with in './data' folder\n\n")
fileName = input('fileName: ')
spath = "data/"+fileName+".xlsx"
dpath = "data/"+fileName+".txt"
# take input from '.xlsm' i.e. excel format 
# return 'list' type data
ob1 = xlsxInput.xlsxInput(spath)
xlsxData = ob1.data
print(xlsxData)
ob3 = messData.PrintCSVData(dpath, xlsxData)
print(ob3.sms)

 
