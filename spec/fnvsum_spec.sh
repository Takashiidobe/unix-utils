HELP_TEXT=$(cat <<-END
Usage: fnvsum [FILE]...
or: fnvsum OPTION
Print an fnv hash of input.

--help     display this help and exit
--version  output version information and exit
END
)

VERSION_TEXT="fnvsum (libc) 0.0.1"

Describe 'fnvsum' 
  fnv() { echo "$1" | build/fnvsum; }
  fnvsum_h() { build/fnvsum -h; }
  fnvsum_help() { build/fnvsum --help; }
  fnvsum_v() { build/fnvsum -v; }
  fnvsum_version() { build/fnvsum --version; }
  fnvsum_err() { build/fnvsum --error; }

  It 'returns `2765235376` when hashing `hi`'
    When call fnv "hi"
    The status should be successful
    The output should eq 2765235376 
  End

  It 'returns `4170400115` when hashing `hello`'
    When call fnv "hello"
    The status should be successful
    The output should eq 4170400115
  End

  It 'returns `252472541` when hashing `""`'
    When call fnv ""
    The status should be successful
    The output should eq 252472541
  End

  It 'returns `1737210820` when hashing `"hi\nhello\n"`'
    When call fnv "hi\nhello\n" 
    The status should be successful
    The output should eq 1737210820
  End

  It 'is called with `-h`'
    When call fnvsum_h
    The output should eq "$HELP_TEXT"
    The status should be successful
  End

  It 'is called with `--help`'
    When call fnvsum_help
    The output should eq "$HELP_TEXT"
    The status should be successful
  End

  It 'is called with `-v`'
    When call fnvsum_v
    The output should eq "$VERSION_TEXT"
    The status should be successful
  End

  It 'is called with `--version`'
    When call fnvsum_version
    The output should eq "$VERSION_TEXT"
    The status should be successful
  End

  It 'is called with an unknown argument'
    When call fnvsum_err
    The output should eq ""
    The status should be failure 
  End
End
