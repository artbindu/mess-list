import xlrd.__init__ as xlrd

class xlsxInput :
    path = None
    sheet = None
    data = None

    def __init__(self, path)    :
        self.path = path
        self.sheet = self.takeInputFromExcel()
        self.data = self.prossingData()

    def takeInputFromExcel(self) :   
        openSheet = xlrd.open_workbook(self.path) 
        sheet = openSheet.sheet_by_index(0) 
        sheet.cell_value(0, 0) 
        return sheet

    def prossingData(self) :
        arrayData = []
        for i in range(self.sheet.nrows) :
            tempArray = []
            for j in range(0,len(self.sheet.row_values(i)))  :
                tempArray.append(self.sheet.row_values(i)[j])
            arrayData.append(tempArray)
        return arrayData

    def display(self) :
        for i in range(0, len(self.data))   :
            print(self.data[i])

