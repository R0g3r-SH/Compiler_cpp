Certainly! Here's the updated README.md with a "Copy" button for each individual command:

```markdown
# Compilation Commands

## Compile using Lex and Yacc
```bash
lex scanner.l
byacc -d parser.y
```
<button id="copyButtonLexYacc" data-clipboard-target="#compileLexYacc">Copy Lex and Yacc Compilation</button>

## Compile using g++ for testing with custom code
```bash
g++ -o tester main_test.cpp lex.yy.c y.tab.c -ll
```
<button id="copyButtonGppTester" data-clipboard-target="#compileGppTester">Copy G++ Compilation for Testing</button>

## Compile using g++ for debugging scanner/lexer with Lex
```bash
g++ -o debug_lex main_debug_lex.cpp lex.yy.c y.tab.c -ll
```
<button id="copyButtonGppDebugLex" data-clipboard-target="#compileGppDebugLex">Copy G++ Compilation for Debugging with Lex</button>

## Compile using g++ for debugging scanner/lexer with Flex
```bash
g++ -o debug_flex main_debug_lex.cpp lex.yy.c y.tab.c -lfl
```
<button id="copyButtonGppDebugFlex" data-clipboard-target="#compileGppDebugFlex">Copy G++ Compilation for Debugging with Flex</button>

# Testing Commands

## Test with custom code using Lex
```bash
./tester input.txt
```
<button id="copyButtonTestLex" data-clipboard-target="#testLex">Copy Lex Testing Command</button>

## Debug scanner/lexer with Lex
```bash
./debug_lex input.txt
```
<button id="copyButtonDebugLex" data-clipboard-target="#debugLex">Copy Lex Debugging Command</button>

## Debug scanner/lexer with Flex
```bash
./debug_flex input.txt
```
<button id="copyButtonDebugFlex" data-clipboard-target="#debugFlex">Copy Flex Debugging Command</button>

<script src="https://cdnjs.cloudflare.com/ajax/libs/clipboard.js/2.0.8/clipboard.min.js"></script>
<script>
    var copyButtons = document.querySelectorAll('[id^="copyButton"]');
    copyButtons.forEach(function(button) {
        button.addEventListener('click', function(event) {
            var targetId = event.target.getAttribute('data-clipboard-target');
            var targetElement = document.querySelector(targetId);
            var clipboard = new ClipboardJS(event.target, {
                target: function() {
                    return targetElement;
                }
            });
            clipboard.on('success', function(e) {
                console.log('Text copied to clipboard');
                e.clearSelection();
            });
            clipboard.on('error', function(e) {
                console.error('Failed to copy text');
            });
            clipboard.destroy();
        });
    });
</script>
```

This README file now includes a "Copy" button for each individual command, making it easier for users to copy specific commands as needed.