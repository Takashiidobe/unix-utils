HELP_TEXT=$(cat <<-END
Usage: false [ignored command line arguments]
or: false OPTION
Exit with a status code indicating failure.

--help     display this help and exit
--version  output version information and exit
END
)

VERSION_TEXT="false (libc) 0.0.1"

Describe 'false' 
  false() { build/false; }
  false_h() { build/false -h; }
  false_help() { build/false --help; }
  false_v() { build/false -v; }
  false_version() { build/false --version; }
  false_err() { build/false --doesntexist; }
 
  It 'is called without arguments'
    When call false 
    The output should eq ""
    The status should be failure 
  End

  It 'is called with `-h`'
    When call false_h
    The output should eq "$HELP_TEXT"
    The status should be successful 
  End

  It 'is called with `--help`'
    When call false_help
    The output should eq "$HELP_TEXT"
    The status should be successful
  End

  It 'is called with `-v`'
    When call false_v
    The output should eq "$VERSION_TEXT"
    The status should be successful
  End

  It 'is called with `--version`'
    When call false_version
    The output should eq "$VERSION_TEXT"
    The status should be successful
  End

  It 'is called with an unknown argument'
    When call false_err
    The output should eq ""
    The status should be failure 
  End
End
