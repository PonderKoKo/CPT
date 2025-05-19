def unionfind_summary(value, _):
    vector = value.GetChildMemberWithName('p')
    vector.SetPreferSyntheticValue(True)
    n = vector.num_children
    sets = [set() for _ in range(n)]
    for i in range(n):
        x = i
        while vector.GetChildAtIndex(x).GetValueAsSigned() >= 0:
            x = vector.GetChildAtIndex(x).GetValueAsSigned()
        sets[x].add(i)
    return list(filter(lambda x: x, sets))

# Displays the sets as virtual children. Has some unfortunate issues because the format name = {type} value can't be changed
class UnionFindPrettifier:
    has_children = True

    def __init__(self, valobj, _):
        self.valobj = valobj
        self.vector = valobj.GetChildMemberWithName('p')
        self.vector.SetPreferSyntheticValue(True)

    def update(self):
        n = self.vector.num_children
        self.sets = [[] for _ in range(n)]
        for i in range(n):
            x = i
            while self.vector.GetChildAtIndex(x).GetValueAsSigned() >= 0:
                x = self.vector.GetChildAtIndex(x).GetValueAsSigned()
            self.sets[x].append(i)
        self.sets = list(filter(lambda x: x, self.sets))
        return False

    def num_children(self):
        return len(self.sets) + 1

    def get_child_at_index(self, index):
        if index == len(self.sets):
            return self.vector
        # I wish we could create a null-value with just the name :(
        return self.valobj.CreateBoolValue(str(self.sets[index]), True)