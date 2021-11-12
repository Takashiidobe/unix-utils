Describe 'md5sum'
  Describe 'with arguments'
	  md5sum() { build/md5sum "$1"; }
	  md5sum_stdin() { echo "$1" | build/md5sum; }

    It 'with input hi'
			When call md5sum "hi"
      The output should eq "764efa883dda1e11db47671c4a3bbd9e"
    End

		It 'with input that is too long'
		  When call md5sum "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
			The stderr should be present
      The stderr should include "was too long to hash with md5."
			The status should eq 1
		End

    It 'with input hi'
			When call md5sum_stdin "hi"
      The output should eq "764efa883dda1e11db47671c4a3bbd9e"
    End

		It 'with input that is too long'
		  When call md5sum "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
			The stderr should be present
      The stderr should include "was too long to hash with md5."
			The status should eq 1
		End
  End
End
