Describe 'uname' 
  Describe 'uname without arguments'
    uname() { build/uname; }
    uname_s() { build/uname -s; }
    uname_a() { build/uname -a; }
    uname_all() { build/uname --all; }
    uname_n() { build/uname -n; }
    uname_nodename() { build/uname --nodename; }


    It 'returns the OS name when called with no arguments'
      When call uname 
      The output should include "Linux"
    End

    It 'returns the OS name when called with -s'
      When call uname_s 
      The output should include "Linux"
    End

    It 'returns the correct string when called with -a'
      When call uname_a 
      The output should include "Linux"
    End

    It 'returns the correct string when called with --all'
      When call uname_all
      The output should eq "Linux"
    End

    It 'returns the correct nodename when called with -n'
      When call uname_n
      The output should eq "Linux"
    End

    It 'returns the correct nodename when called with --nodename'
      When call uname_nodename
      The output should eq "Linux"
    End
  End
End
