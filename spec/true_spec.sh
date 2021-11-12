HELP_TEXT=$(cat <<-END
Usage: true [ignored command line arguments]
or: true OPTION
Exit with a status code indicating success.

--help     display this help and exit
--version  output version information and exit
END
)

VERSION_TEXT="true (libc) 0.0.1"

Describe 'true' 
  true() { build/true; }
  true_h() { build/true -h; }
  true_help() { build/true --help; }
  true_v() { build/true -v; }
  true_version() { build/true --version; }
  true_err() { build/true --doesntexist; }
 
  It 'is called without arguments'
    When call true 
    The output should eq ""
    The status should be successful
  End

  It 'is called with `-h`'
    When call true_h
    The output should eq "$HELP_TEXT"
    The status should be successful
  End

  It 'is called with `--help`'
    When call true_help
    The output should eq "$HELP_TEXT"
    The status should be successful
  End

  It 'is called with `-v`'
    When call true_v
    The output should eq "$VERSION_TEXT"
    The status should be successful
  End

  It 'is called with `--version`'
    When call true_version
    The output should eq "$VERSION_TEXT"
    The status should be successful
  End

  It 'is called with an unknown argument'
    When call true_err
    The output should eq ""
    The status should be successful
  End
End
