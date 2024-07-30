import re

class ArgumentAnalyser:
    def analyse_arguments(self, args):
        arg_list = []
        for arg in args.split(','):
            self._add_args(arg_list, arg)
        return arg_list
    
    def _add_args(self, arg_list, arg):
        match = re.match('\\s*([0-9]+)-([0-9]+)', arg)
        if match and len(match.groups()) == 2:
            groups = match.groups()
            self._add_argument_range(arg_list, groups[0], groups[1])
        else:
            arg_list.append(arg.lstrip())

    def _add_argument_range(self, arg_list, value_from, value_to):
        for v in range(int(value_from), int(value_to)+1):
            arg_list.append(str(v))
