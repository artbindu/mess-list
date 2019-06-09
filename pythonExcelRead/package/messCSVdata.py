class PrintCSVData :
    # @ calling from main.py
    def __init__(self, dFile, csvData) :
        self.data = csvData
        self.dData = self.removeData()
        # return sms to main.py
        self.sms = self.saveInFile(dFile)

    # removing the excel data
    def removeData(self) :
        arr = [
            'year', 'month name',
            'total member',
            'total expenditure',
            'electric bill details',
            'elect starting unit','elect ending unit','unit bill',
            'mess diposite','expenditure',
        ]
        for i in range(0,20) :
            arr.append('mem'+str(i))
            arr.append('exp'+str(i))
        return arr

    # save excel data into '.txt' file
    def saveInFile(self, dFile) :
        print(dFile)
        monthsDate = 0
        f = open(dFile,'w')
        st = ''
        flag = 0
        for x in self.data :
            if(str(x[0]).lower() == 'daily date') :
                flag = 1
            ckLine = self.removeLine(str(x[0]))
            if(ckLine) :
                continue

            if(monthsDate == 0 ) :
                flag = 0
                monthsDate = self.months_find(monthsDate, str(x[1]))
            if(flag == 1) :
                x[0] = 'Y' # change input-date  --> 'Y'
                x[9] = 'Y' # change output-date  --> 'Y'
                if(monthsDate>0) :
                    monthsDate = monthsDate - 1
            for y in x :
                add = self.chakingDataType(y)
                if(add) :
                    st += '\t\t'+str(add)
            st += '\n'
        st += '\n\n\n\n' + self.defaultPart()
        f.write(st) 
        f.close()
        return 'done'
    # remove the excel sheet lines
    def removeLine(self, a) :
        arr = ['color details', 'daily date', 'total', 'member id', 'expenditure id', 'border name', 'extra charges', 'egg', 'guest']
        for x in arr :
            if(a.lower() == x) :
                return True
        return False

    def chakingDataType(self, a) :
        if(str(type(a)) == '<class \'str\'>') :
            a = a.lower()
            if a not in self.dData :
                return a
            else :
                return None
        elif(str(type(a)) == '<class \'float\'>' or str(type(a)) == '<class \'int\'>' ) :
            # print(a)
            a = float(a)
            if(a == 0.0) :
                return str(0)
            try :
                return(int(a))
            except ValueError :
                return float(a)
        else :
            return a
    def defaultPart(self) :
        st = ''
        arr = ['y', 'n', 'y', input('massi cash: '), 'y', 'y', input('Gas Cost: '), 'y', input('Garbase cash: ')]
        for x in arr :
            st += '\n' + str(x)
        return st

    def months_find(self, data, name) :
        month = {
            'january' : 31,
            'february' : 28,
            'march' : 31,
            'april' : 30,
            'may' : 31,
            'june': 30,
            'july': 31,
            'august': 31,
            'september' : 30,
            'october': 31,
            'november' : 30,
            'december' : 31
        }
        try :
            return month[str(name)]
        except KeyError :
            return data
