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
      The output should eq "Darwin "  
    End

    It 'returns the OS name when called with -s'
      When call uname_s 
      The output should eq "Darwin "  
    End

    It 'returns the correct string when called with -a'
      When call uname_a 
      The output should eq "Darwin Takashis-MacBook-Pro.local 19.6.0 Darwin Kernel Version 19.6.0: Thu Jun 18 20:49:00 PDT 2020; root:xnu-6153.141.1~1/RELEASE_X86_64 x86_64 Darwin "  
    End

    It 'returns the correct string when called with --all'
      When call uname_all
      The output should eq "Darwin Takashis-MacBook-Pro.local 19.6.0 Darwin Kernel Version 19.6.0: Thu Jun 18 20:49:00 PDT 2020; root:xnu-6153.141.1~1/RELEASE_X86_64 x86_64 Darwin "  
    End

    It 'returns the correct nodename when called with -n'
      When call uname_n
      The output should eq "Takashis-MacBook-Pro.local "
    End

    It 'returns the correct nodename when called with --nodename'
      When call uname_nodename
      The output should eq "Takashis-MacBook-Pro.local "
    End
  End
End
