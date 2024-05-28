import unittest


class MyTest(unittest.TestCase):
    def test_output(self):

        # Load expected output from files
        with open("./test/expected_output_1.txt", "r") as file:
            expected_output = file.read()

        # Load actual output from generated file
        with open("./test/output.txt", "r") as file:
            actual_output = file.read()

        # Compare actual output with expected output
        self.assertEqual(actual_output, expected_output)

    def test_quads(self):
        # Load expected quads from files
        with open("./test/expected_quads_1.txt", "r") as file:
            expected_quads = file.read()

        # Load actual quads from generated file
        with open("./test/quads.txt", "r") as file:
            actual_quads = file.read()

        # Compare actual quads with expected quads
        self.assertEqual(actual_quads, expected_quads)

if __name__ == '__main__':
    unittest.main()
