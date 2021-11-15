Describe 'chmod'
  chmod() { build/chmod $1 $2; }
  permissions() { stat -c '%a' $1; }

	Before
		touch spec/test_files/chmod/1.txt
    chmod 0755 spec/test_files/chmod/1.txt
	End

  It 'changes the file to the specified mode'
		When call permissions spec/test_files/chmod/1.txt
		The output should eq 755
  End
End
