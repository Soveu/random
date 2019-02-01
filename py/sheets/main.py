#!which python
from googleapiclient.discovery import build
from httplib2 import Http
from oauth2client import file, client, tools

# If modifying these scopes, delete the file token.json.
SCOPES = 'https://www.googleapis.com/auth/spreadsheets.readonly'

# The ID and range of a sample spreadsheet.
SPREADSHEET_ID = '1trCGf0eAXbX4h-Bq30obQoGqXQayZIHR0w7cUHZG5R0'
RANGE_NAME = "'Tablica wpłat'!A1:F32"

def xToBool(d):
    t = []

    for x in d:
        t.append(len(x) > 0)

    return t

class Target():
    def __init__(self, t, n, e):
        self.target = t
        self.name = n
        self.each = e

class Targets():
    def __init__(self, t):
        self.targets = []
        data = []
        for row in t:
            data.append(row[2:])

        for i in range(len(data[0])):
            self.targets.append(Target(data[0][i], data[1][i], data[2][i]))

    def __str__(self):
        s = '\t\t'
        for a in self.targets:
            s += a.target + '\t'

        s += '\n\t\t'

        for b in self.targets:
            s += b.name[:6] + '\t\t'

        s += '\n\t\t'

        for c in self.targets:
            s += c.each + '\t\t'

        s += '\n\t\t'

        return s

class Person():
    def __init__(self, n, d):
        self.name = n
        self.debt = xToBool(d)

    def __str__(self):
        s = self.name[:14] + ':\t'

        for b in self.debt:
            if b:
                s += 'x'

            s += '\t\t'

        return s
    
    def czyZalega(self):
        for zap in self.debt:
            if not zap:
                return True

        return False

class Persons():
    def __init__(self, t):
        self.persons = []
        for row in t:
            self.persons.append(Person(' '.join(row[:2]), row[2:]))

    def __str__(self):
        s = ''

        for person in self.persons:
            s += person.__str__() + '\n'

        return s

    def ktoZalega(self):
        osoby = []

        for x in self.persons:
            if x.czyZalega():
                osoby.append(x.name)

        return osoby

 
class PiniondzeKlasowe(Targets, Persons):
    def __init__(self, t):
        Targets.__init__(self, t[:3])
        Persons.__init__(self, t[3:])

    def __str__(self):
        return Targets.__str__(self) + '\n' + Persons.__str__(self)
    
    def ktoZalega(self):
        return Persons.ktoZalega(self)


#def main():
#    store = file.Storage('token.json')
#    creds = store.get()
#    if not creds or creds.invalid:
#        flow = client.flow_from_clientsecrets('credentials.json', SCOPES)
#        creds = tools.run_flow(flow, store)
#    service = build('sheets', 'v4', http=creds.authorize(Http()))
#
#    # Call the Sheets API
#    result = service.spreadsheets().values().get(spreadsheetId=SPREADSHEET_ID,
#                                                range=RANGE_NAME).execute()
#    values = result.get('values', [])
#
#    if not values:
#        print('No data found.')
#        return
#    
#    p = PiniondzeKlasowe(values)
#    print(p)
#    print(p.ktoZalega())
#   
#
#
#if __name__ == '__main__':
#    main()

values = [
        ['', '', '29,98 zł', '116,00 zł', '105,00 zł', '377,00 zł'], 
        ['Osoba', '', 'Papier', 'Kwiaty', 'Papier 2', 'Kino'], 
        ['Imię', 'Nazwisko', '1,00 zł', '4,00 zł', '4,00 zł', '13,00 zł'], 
        ['Katarzyna', 'Bańkowska', 'x', '', 'x', 'x'], 
        ['Michał', 'Bednarz', 'x','x', 'x', 'x'], 
        ['Mateusz', 'Cebula', 'x', 'x', 'x', 'x'], 
        ['Rafał', 'Chmielewski', 'x', 'x', 'x', 'x'], 
        ['Kuba', 'Domagała', 'x', 'x', 'x'], 
        ['Jędrzej', 'Drąg', 'x', 'x', 'x', 'x'], 
        ['Marek', 'Gogolok', 'x', 'x', 'x', 'x'], 
        ['Szymon', 'Habrych', 'x', 'x', 'x', 'x'], 
        ['Mateusz', 'Hurnik', 'x', 'x', 'x', 'x'], 
        ['Patrycja', 'Kolasa', 'x', 'x', 'x', 'x'], 
        ['Julia', 'Kołodziej', 'x', 'x', 'x'], 
        ['Tycjan', 'Kołodziej', 'x', 'x', 'x', 'x'], 
        ['Patryk', 'Kordisch', 'x', 'x', 'x', 'x'], 
        ['Alosza', 'Korolczuk', 'x', 'x', 'x', 'x'], 
        ['Michał', 'Kowalski', 'x', 'x', 'x', 'x'], 
        ['Tomasz', 'Marx', 'x', 'x', 'x', 'x'], 
        ['Julia', 'Mazur', 'x', 'x', 'x', 'x'], 
        ['Marcel', 'Niesłony', 'x', 'x', 'x', 'x'], 
        ['Wiktoria', 'Ozimek', 'x', 'x', 'x', 'x'], 
        ['Mateusz', 'Przymuszała', 'x', 'x', 'x', 'x'], 
        ['Kajetan', 'Sarnowski', 'x', 'x', 'x', 'x'], 
        ['Kamil', 'Selega', 'x', 'x', 'x', 'x'], 
        ['Damian', 'Serwuszok', 'x', 'x', 'x', 'x'], 
        ['Kuba', 'Sikorski', '', '', '', 'x'], 
        ['Adam', 'Szczepaniak', 'x', 'x', 'x', 'x'], 
        ['Szymon', 'Szendzielorz', 'x', 'x', 'x', 'x'], 
        ['Mikołaj', 'Szymanek', 'x', 'x', 'x', 'x'], 
        ['Michał', 'Wach', 'x'], 
        ['Julian', 'Zieliński', 'x', 'x', 'x','x']
]


p = PiniondzeKlasowe(values)
print(p)
print(p.ktoZalega())

