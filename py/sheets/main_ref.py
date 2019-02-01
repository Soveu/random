import json #it is here coz code looks wierdly without any imports

class Person():
    """This class contains all personal information of one person """
    def __init__(self, values):
        self.Name = values[0]
        self.Surname = values[1]
        self.record=[] # an list of all goal payments True if paid False otherwise
        for a in values[2:]:
            self.record.append(a=='x')

    def __repr__(self):
        return "{} {}".format(self.Name,self.Surname)

class Goal():
    """This class symbolises one goal"""
    def __init__(self,goal,tag,payment, index):
        self.max=goal
        self.tag = tag
        self.perPerson=payment
        self.index=index


class ClassMoneyManager():
    """This class manages all the class money"""
    def __init__(self,values):
        maxVals = values[0]
        tags = values[1]
        personVals = values[2]
        self.goals=[]
        for i,a in enumerate(tags[2:]):
            self.goals.append(Goal(maxVals[i+2],a,personVals[i+2],i))

        people = values[3:]
        self.people=[]
        for a in people:
            if len(a) != len(tags):
                for b in range(len(tags)-len(a)):
                    a.append('')
            self.people.append(Person(a))

    """Returns a list of people who need to pay for provided goal
    goal can be given by either id or tag"""
    def whoOwsFor(self,index):
        if type(index) == str:
            for a in self.goals:
                if a.tag == index:
                    index = a.index
        ret=[]
        for p in self.people:
            if not p.record[index]:
                ret.append(p)
        return ret

    """Returns a 2 dimensional list of all debters with the goal name at 0"""
    def whoOws(self):
        ret=[]
        for a in self.goals:
            b = self.whoOwsFor(a.index)
            b.insert(0,a.tag)
            ret.append(b)
        return ret


def test():
    values=[
        ['', '',                    '29,98 zł', '116,00 zł', '105,00 zł', '377,00 zł'], 
        ['Osoba', '',               'Papier', 'Kwiaty', 'Papier 2', 'Kino'], 
        ['Imię', 'Nazwisko',        '1,00 zł', '4,00 zł', '4,00 zł', '13,00 zł'], 
        ['Katarzyna', 'Bańkowska',  'x', '', 'x', 'x'], 
        ['Michał', 'Bednarz',       'x','x', 'x', 'x'], 
        ['Mateusz', 'Cebula',       'x', 'x', 'x', 'x'], 
        ['Rafał', 'Chmielewski',    'x', 'x', 'x', 'x'], 
        ['Kuba', 'Domagała',        'x', 'x', 'x'], 
        ['Jędrzej', 'Drąg',         'x', 'x', 'x', 'x'], 
        ['Marek', 'Gogolok',        'x', 'x', 'x', 'x'], 
        ['Szymon', 'Habrych',       'x', 'x', 'x', 'x'], 
        ['Mateusz', 'Hurnik',       'x', 'x', 'x', 'x'], 
        ['Patrycja', 'Kolasa',      'x', 'x', 'x', 'x'], 
        ['Julia', 'Kołodziej',      'x', 'x', 'x'], 
        ['Tycjan', 'Kołodziej',     'x', 'x', 'x', 'x'], 
        ['Patryk', 'Kordisch',      'x', 'x', 'x', 'x'], 
        ['Alosza', 'Korolczuk',     'x', 'x', 'x', 'x'], 
        ['Michał', 'Kowalski',      'x', 'x', 'x', 'x'], 
        ['Tomasz', 'Marx',          'x', 'x', 'x', 'x'], 
        ['Julia', 'Mazur',          'x', 'x', 'x', 'x'], 
        ['Marcel', 'Niesłony',      'x', 'x', 'x', 'x'], 
        ['Wiktoria', 'Ozimek',      'x', 'x', 'x', 'x'], 
        ['Mateusz', 'Przymuszała',  'x', 'x', 'x', 'x'], 
        ['Kajetan', 'Sarnowski',    'x', 'x', 'x', 'x'], 
        ['Kamil', 'Selega',         'x', 'x', 'x', 'x'], 
        ['Damian', 'Serwuszok',     'x', 'x', 'x', 'x'], 
        ['Kuba', 'Sikorski',        '', '', '', 'x'], 
        ['Adam', 'Szczepaniak',     'x', 'x', 'x', 'x'], 
        ['Szymon', 'Szendzielorz',  'x', 'x', 'x', 'x'], 
        ['Mikołaj', 'Szymanek',     'x', 'x', 'x', 'x'], 
        ['Michał', 'Wach',          'x'], 
        ['Julian', 'Zieliński',     'x', 'x', 'x','x']
    ]
    p = ClassMoneyManager(values)
    print(p.whoOws())

if __name__ == '__main__':
    test()