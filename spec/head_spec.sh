HELP_TEXT=$(cat <<-END
Usage: head [ignored command line arguments]
or: head OPTION
Exit with a status code indicating success.

--help     display this help and exit
--version  output version information and exit
END
)

VERSION_TEXT="head (libc) 0.0.1"

Describe 'head' 
  head() { build/head; }
  head_file() { build/head spec/test_files/head_file.txt; }
  head_2_files() { build/head spec/test_files/head_file.txt spec/test_files/head_file2.txt; }
  head_h() { build/head -h; }
  head_help() { build/head --help; }
  head_v() { build/head -v; }
  head_version() { build/head --version; }
  head_err() { build/head --doesntexist; }
 
  It 'is called without arguments'
    When call head 
    The output should eq ""
    The status should be successful
  End

  It 'is called on the test file'
    RES=$(cat <<-END
===> spec/test_files/head_file.txt <===
VxGX2VUgLpwTo8rxMVLdMsu318lianjWOA1YvKMrQFdgnIR89yxsLK3tCQWwQczdjKFSn2jqzOlTQfMw
UebF4WH3P0ArLW2v47ONOuUSBdhcTk0nNlEhcF8cMP0Fq0yD7HWgiVlruzNU9ejsBMXF7vP34XaraM7W
09iCRM34bKvl2T0ZMmqb84tNesGQaNRNKF50IHvBDfAlaMpEhZdas2b6uKzLNBzmUUeeqWckinzqFUw3
LI607Y2uNwaVSoSkpbb8Dg8T0AIrYQHj0TEX8r57AEBGAx1k5xhcbo4zZPw0w4hHVeAAJZACa9LSL0kC
sZm40kTIESETgKaQKVib5ePpTNgcW9tkQHgnmnRbL74X8r7FRLm5p8C8J417cTZnXVNUKvx7cX27lWnm
P387PF3q2NQn9nNa8aLvW2UoxtBZW1EIOSjfzwUgfk0q2vNIgS4YOnj2RmYa4CZGwH12VP1ZWK53jipe
mhweVA1fEJYXGME8lerq7eP18FXtuCfS7fKY0ugcyZMNyQSAkcjKsR5WFNFGHo3bCg6xK8n86ah7mAet
xyKMaYTiTVSBzG8RLbQ0PnAI3mFMDT0qFHXQIEsxR4d67Q6bRYn2oB2nUtK9xTeWRaWgKao4sfFRvoFX
tqCWHKOaR4B1ZVEfRUZ76FyKOPmd2pXy648jVgJxzTOjVvXO518NaVZWT4IcBd4hNkam9sMcAIdVj7mC
0uhPT0btGRhr8bvMb84ih0vnCe7m6ml2ozIBArlA8GuS7UB6FnMYvEudbJWvVmTnXUUWEdSxi6I3pb1B
END
)
    When call head_file
    The output should eq "$RES"
    The status should be successful
  End

  It 'is called on two files'
    RES=$(cat <<-END
===> spec/test_files/head_file.txt <===
VxGX2VUgLpwTo8rxMVLdMsu318lianjWOA1YvKMrQFdgnIR89yxsLK3tCQWwQczdjKFSn2jqzOlTQfMw
UebF4WH3P0ArLW2v47ONOuUSBdhcTk0nNlEhcF8cMP0Fq0yD7HWgiVlruzNU9ejsBMXF7vP34XaraM7W
09iCRM34bKvl2T0ZMmqb84tNesGQaNRNKF50IHvBDfAlaMpEhZdas2b6uKzLNBzmUUeeqWckinzqFUw3
LI607Y2uNwaVSoSkpbb8Dg8T0AIrYQHj0TEX8r57AEBGAx1k5xhcbo4zZPw0w4hHVeAAJZACa9LSL0kC
sZm40kTIESETgKaQKVib5ePpTNgcW9tkQHgnmnRbL74X8r7FRLm5p8C8J417cTZnXVNUKvx7cX27lWnm
P387PF3q2NQn9nNa8aLvW2UoxtBZW1EIOSjfzwUgfk0q2vNIgS4YOnj2RmYa4CZGwH12VP1ZWK53jipe
mhweVA1fEJYXGME8lerq7eP18FXtuCfS7fKY0ugcyZMNyQSAkcjKsR5WFNFGHo3bCg6xK8n86ah7mAet
xyKMaYTiTVSBzG8RLbQ0PnAI3mFMDT0qFHXQIEsxR4d67Q6bRYn2oB2nUtK9xTeWRaWgKao4sfFRvoFX
tqCWHKOaR4B1ZVEfRUZ76FyKOPmd2pXy648jVgJxzTOjVvXO518NaVZWT4IcBd4hNkam9sMcAIdVj7mC
0uhPT0btGRhr8bvMb84ih0vnCe7m6ml2ozIBArlA8GuS7UB6FnMYvEudbJWvVmTnXUUWEdSxi6I3pb1B

===> spec/test_files/head_file2.txt <===
wNyfELp991ZJgPwz9sRSioJ6WPF4OLdsqxfY95NQn6jkP55Kqbi6isXjsN3m1FUBAON94fKt2t88tBkK
akbLHlfHfYkftdAp0KVLsALXN75yRz03z1J5AxcIqp2F1QvKblappzH4S1fvRHBiAinoIOrL6WIzGbNI
DLQAHT3pJ2ejvr0p0acJG2ExPNst4SCYYKRO61jHiwlAoP0s1oRJhvTnMT6h6VotlLITUxBndakMWmCO
9VbZhQi8KiV81jYg951ZJNnx4nCEqVkqXgGQpQbqaiOTs538ux5LjpNSFHU7ixWJdWQgQFz6t4WqYc7e
ASCYrwKQNrUwLJ7VdPmuOyN8wiQ15ISgHaBtDGe8aUsXZgTcCdrMzHobMJns4iG3UiulrZMxkylIvsOp
k9aLV2NpA8HAW4vdv4x8RlilmA2mEZaKbZOIzC0FMmHftfXSyr6NFzOHUOloQezpHrTUhn9tqVyOElws
7WEbv0Ioyyo11G4CvcNW97d1a7sb9m9P71XaY6h4XPQReXWTfH4qjLPecCN59Vpm5ehi48J8nHoVG53I
lwVe2dVa9dwMuqBQvd6M6ffQapxmqVve0yzlGJ7soPZcKvlO6WKDbAB81Cu1V69ufkZU4370VQRaBY9L
fR77DdTHGANAJcn5KQT3CxRaOFj0A8IyOo73r7lfCaC0Ej1uvkmxAJi4JsNY2IdVSgXl1BoLELiagTZE
hVzSavYH7T2HyZTybXbXyMijM0oVhxE9JPi2PcDASg1YEauURpVS4Kie7NtGAlvngQTSAIhdpNsCOQxX
END
)
    When call head_2_files
    The output should eq "$RES"
    The status should be successful
  End

  # It 'is called with `-h`'
  #   When call head_h
  #   The output should eq "$HELP_TEXT"
  #   The status should be successful
  # End

  # It 'is called with `--help`'
  #   When call head_help
  #   The output should eq "$HELP_TEXT"
  #   The status should be successful
  # End

  # It 'is called with `-v`'
  #   When call head_v
  #   The output should eq "$VERSION_TEXT"
  #   The status should be successful
  # End

  # It 'is called with `--version`'
  #   When call head_version
  #   The output should eq "$VERSION_TEXT"
  #   The status should be successful
  # End

  It 'is called with an unknown argument'
    ERR_TEXT=$(cat <<-END
head: invalid option -- '--doesntexist'
Try 'head --help' for more information.
END
    )
    When call head_err
    The output should eq "$ERR_TEXT"
    The status should be failure
  End
End
