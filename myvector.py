import lldb
import traceback

class MyVectorSyntheticProvider:
    def __init__(self, valobj, internal_dict):
        self.valobj = valobj
        print('type is ', type(valobj))
        self.update()

    def update(self):
        try:
            self.size = self.valobj.GetChildMemberWithName("size").GetValueAsUnsigned()
            print("self.size is", self.size)
            self.data = self.valobj.GetChildMemberWithName("data")
            print("self.data is", self.data)
        except:
            self.size = 0
            self.data = None

    def num_children(self):
        return self.size

    def get_child_index(self, name):
        try:
            return int(name.lstrip('[').rstrip(']'))
        except:
            return -1

    def get_child_at_index(self, index):
        print("get type", self.data.GetType().GetName())
        print("get type", self.data.GetType().GetPointeeType().GetName())
        if self.data:
            offset = index * self.data.GetType().GetPointeeType().GetByteSize()
            return self.data.CreateChildAtOffset(f"[{index}]", offset, self.data.GetType().GetPointeeType())
        return None

    def has_children(self):
        return self.size > 0

class MyListSyntheticProvider:
    def __init__(self, valobj, internal_dict):
        self.valobj = valobj
        self.update()

    def update(self):
        self.data = []
        try:
          node = self.valobj
          while node.IsValid():
            data_ = node.GetChildMemberWithName("data")
            ele_ = data_.CreateValueFromAddress(
                f"{len(self.data)}th-child",
                data_.GetAddress().GetLoadAddress(lldb.debugger.GetSelectedTarget()),
                data_.GetType())
            
            print(f'append a data ele to {self.valobj.GetName()}')
            self.data.append(ele_)
            next_ = node.GetChildMemberWithName("next")
            if not next_.IsValid() or next_.GetValueAsUnsigned() == 0:
              break
            node = next_.Dereference()
        except:
            print(traceback.format_exc())

    def num_children(self):
        return len(self.data)

    def get_child_index(self, name):
        try:
            return int(name.rstrip('th-child'))
        except:
            return -1

    def get_child_at_index(self, index):
        if self.data:
            return self.data[index]
        return None

    def has_children(self):
        return self.size > 0

def __lldb_init_module(debugger, dict):
    debugger.HandleCommand('type synthetic add -l myvector.MyVectorSyntheticProvider MyVector')
    debugger.HandleCommand('type synthetic add -l myvector.MyListSyntheticProvider Node')
