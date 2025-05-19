def stdarray_summary(value, _):
    value.SetPreferSyntheticValue(True)
    return '[ ' + ', '.join([value.GetChildAtIndex(i).GetValue() for i in range(value.num_children)]) + ' ]'

class StdArrayElemForwarder:
    has_children = True
    def __init__(self, valobj, _):
        self.valobj = valobj

    def update(self):
        self.elems_member = self.valobj.GetChildMemberWithName('__elems_')
        return False

    def num_children(self):
        return self.elems_member.num_children

    def get_child_at_index(self, index):
        return self.elems_member.GetChildAtIndex(index)
