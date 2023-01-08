What are the other special symbols used in Makefile like $@ ?
================================================================
In a Makefile, `$@` is a special symbol that represents the target of a rule. There are several other special symbols that can be used in a Makefile as well:

`$<` : This symbol represents the name of the first prerequisite of the rule. For example, if the rule is `foo: bar baz`, then `$<`  would be replaced with bar.

`$^` : This symbol represents the names of all the prerequisites of the rule, separated by spaces. For example, if the rule is `foo: bar baz`, then `$^` would be replaced with `bar baz`.

`$*` : This symbol represents the stem of the target. In a pattern rule, the stem is the part of the target that matches the % character in the target pattern. For example, if the rule is `%.o: %.c`, and the target is `foo.o`, then `$*`  would be replaced with `foo`.

`$+` : This symbol is similar to `$^` , but it includes all the prerequisites, even if there are duplicates. For example, if the rule is `foo: bar baz bar`, then `$+`  would be replaced with `bar baz bar`.

`$?` : This symbol represents the names of all the prerequisites that are newer than the target. For example, if the rule is `foo: bar baz`, and baz is newer than foo, but bar is not, then $? would be replaced with baz.