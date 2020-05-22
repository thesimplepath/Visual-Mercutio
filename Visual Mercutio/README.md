# Visual Mercutio C++ Code Convention

1. Indentation
2. Declaring variables
3. Declaring enumerators
4. Whitespace
5. Braces
6. Parentheses
7. Switch statements
8. Jump statements (break, continue, return, and goto)
9. Line breaks
10. General exceptions

## 1. Indentation
4 spaces are used for indentation. Tabs aren't allowed. Elements are aligned in columns whenever possible.

```cpp
// wrong
int height;
int width;
char* pNameOfThis = NULL;
char* pNameOfThat = NULL;
std::size index = 0;
std::size offset = 0;

// correct
int       height;
int       width;
char*     pNameOfThis = NULL;
char*     pNameOfThat = NULL;
std::size index       = 0;
std::size offset      = 0;
```

## 2. Declaring variables
Declare each variable on a separate line. Avoid short or meaningless names (e.g "a", "rbarr", "nughdeget"). Single character variable names are only admitted for counters and temporaries, where the purpose of the variable is obvious. Wait when declaring a variable until it is needed.

```cpp
// wrong
int a, b;
char* c, *d;

// correct
int   height;
int   width;
char* pNameOfThis;
char* pNameOfThat;
```

Variables and functions start with a lower-case letter, variables owning a pointer start with the "p" letter. Each consecutive word in a variable's name starts with an upper-case letter. Avoid abbreviations.

```cpp
 // wrong
 short Cntr;
 char  ITEM_DELIM = ' ';
 void* custom;

 // correct
 short counter;
 char  itemDelimiter = ' ';
 void* pCustom;
```

Classes always start with an upper-case letter, prefixed with "PSS_" (PSS_Document). Nested classes start with a "I" followed by an upper case letter (IData). All the functions start with an upper-case letter (GetInfo()). Acronyms are camel-cased (e.g. IXmlStreamReader, not IXMLStreamReader).

## 3. Declaring enumerators
Public enumerators starts with the "E" letter, whereas nested enumerators start with "IE". Add a prefix of one or two letters matching with the enumerator name to avoid confusion between the enumerators which may contain the same item (e.g IE_DS_Data for IEDataSource enumerator, and IE_DT_Data for DataType enumerator). Avoid short or meaningless names (e.g "IE_A", "IE_FmtDoc", "IE_NmSpcCtrlr"). Each enumeated items start with "E_" if the enumerator is global, or with "IE_" if the enumerator is nested. Acronyms are camel-cased (e.g. IE_XmlDataSource, not IE_XMLDataSource).

```cpp
// wrong
enum DataSource {FILE, memory, Stream};
enum dataType
{
    FILE,
    memory,
    Stream
};

// correct
enum EDataSource
{
    E_DS_File,
    E_DS_Memory,
    E_DS_Stream
};

enum IEDataType
{
    IE_DT_File,
    IE_DT_Memory,
    IE_DT_Stream
};
```

## 4. Whitespace
Use blank lines to group statements together where suited. Always use only one blank line. Always use a single space after a keyword:

```cpp
// wrong
if(foo){
}

// correct
if (foo)
{}
```

For pointers or references, always use a single space between "\*" or "&" and the variable name, but no space between the "\*" or "&" and the type:

```cpp
char* pX;

const std::string& myString;

const char* const pName = "hello";
```

Surround binary operators with spaces, leave a space after each comma. No space after a cast. Avoid C-style casts when possible.

```cpp
// wrong
char* pBlockOfMemory = (char*)malloc(data.size());

// correct
char* pBlockOfMemory = reinterpret_cast<char*>(malloc(data.size()));
```

Do not put multiple statements on one line. By extension, use a new line for the body of a control flow statement:

```cpp
// wrong
if (foo) bar();

// correct
if (foo)
    bar();
```

## 5. Braces
The opening and closing braces go on the next line after the statement. Empty braces remains on the same line.

```cpp
// wrong
if (codec) {
    ++index;
    DoSomething();
}
else
{
}

// correct
if (codec)
{
    ++index;
    DoSomething();
}
else
{}
```

Use curly braces only when the body of a conditional statement contains more than one line.

```cpp
// wrong
if (address.isEmpty())
{
	return false;
}

for (int i = 0; i < 10; ++i)
{
	Print("%i", i);
}

// correct
if (address.isEmpty())
	return false;

for (int i = 0; i < 10; ++i)
	Print("%i", i);
```

Put an indent for the case statement. Put the else if statements on 2 separate lines, and keep the code blocks aligned.

```cpp
// wrong
if (firstCondition)
{
    ...
}
    else if (secondCondition)
    {
        ...
    }
        else
        {
            ...
        }

switch (condition)
{
case 0:
    ...
case 1:
    ...
}

// correct
if (firstCondition)
{
    ...
}
else
if (secondCondition)
{
    ...
}
else
{
    ...
}

switch (condition)
{
    case 0:
        ...

    case 1:
        ...
}
```

Don't use curly braces when the body of a conditional statement is empty, or put it on a separate line.

```cpp
// wrong
while (a) {}

// correct
while (a);

while (a)
{}
```

## 6. Parentheses
Use parentheses to group expressions:

```cpp
// wrong
if (a && b || c)

// correct
if ((a && b) || c)

// wrong
a + b & c

// correct
(a + b) & c
```

## 7. Switch statements
The case labels are indented one column on the right from the switch. Every case must have a break (or return) statement at the end, unless another case follows immediately.

```cpp
switch (myEnum)
{
    case Value1:
        doSomething();
        break;

    case Value2:
    case Value3:
        doSomethingElse();

    default:
        defaultHandling();
        break;
}
```

## 8. Jump statements (break, continue, return, and goto)
The 'goto' instructions are prohibited, please don't use them, favorize the usage of a sub function instead. Do not put 'else' after jump statements:

```cpp
// wrong
if (thisOrThat)
	return;
else
	somethingElse();

// correct
if (thisOrThat)
	return;

somethingElse();
```

<b>Exception</b> If the code is inherently symmetrical, use of 'else' is allowed to visualize that symmetry

## 9. Line breaks
Keep lines shorter than 120 characters; wrap if necessary. Comment/apidoc lines should also be kept below 120 columns of actual text. Adjust to the surroundings, and try to flow the text in a way that avoids "jagged" paragraphs. Commas go at the end of wrapped lines; operators go at the end of the current lines.

```cpp
// wrong
if (longExpression
+ otherLongExpression
+ otherOtherLongExpression)
{}

// correct
if (longExpression      +
    otherLongExpression +
    otherOtherLongExpression)
{}
```

<b>Exception</b> switch...case statements containing long instructions which may be kept on one line.

## 10. General exceptions
When strictly following a rule makes your code look bad, feel free to break it. If there is a dispute in any given source code file, the maintainer has the final say on the accepted style.

# Annexe
##Modules explanation
The Visual Mercutio modules are organized as follow:

### Include
This module contains the header files to include globally.

### zBaseLib
This module contains the basic class intrfaces, common functions, helpers and resources to use through the whole application.

### zBaseSym
This module contains the basic class intrfaces, common functions and, helpers and resources which bounds the symbols.

### zConversion
This module contains the basic string conversion and encoding functions.

### zDB
This module contains the basic functionalities to connect to a DAO database.

### zEvent
This module contains the basic event dispatcher which will be used in the whole application.

### zFormsRes
This module contains the global form resources.

### zMediator
This module contains the basic application classes.

### zModel
This module contains the basic Visual Mercutio models, with their associated symbols, which are built above the symbols declared in zBaseSym.

### zModelBP
This module contains the basic Visual Mercutio Banking Process models, with their associated symbols, built above the models and symbols declared in zModel.

### zModelWeb
This module contains the classes and functions to export the model as HTML pages.

### zProcess32
This module contains the main application. This is also the default project to build.

### zProperty
This module contains the basic properties system.

### zPtyMgr
This module contains the properties manager, and associated views.

### zRBPPropEn
This module contains the English localized resources for the Banking Process properties.

### zRBPPropFr
This module contains the French localized resources for the Banking Process properties.

### zRBPPropGr
This module contains the German localized resources for the Banking Process properties.

### zReport
This module contains the basic classes and functions to generate a Mercutio report.

### zReportBP
This module contains the classes and functions to generate a Banking Process Mercutio report.

### zReportWeb
This module contains the classes and functions to export a Banking Process Mercutio report to HTML pages.

### zRes32
This module contains the global system 32 resources.

### zResMgr
This module contains the resource manager.

### zRMdlBPEn
This module contains the English localized Model Banking Process resources.

### zRMdlBPFr
This module contains the French localized Model Banking Process resources.

### zRMdlBPGr
This module contains the German localized Model Banking Process resources.

### zScty
This module contains the security and product key manager. <b>NOTE</b> that this module is obsolete as the Visual Mercutio source code is now free and open source.

### zSOAP
This module contains the SOAP protocol to publish the Visual Mercutio Banking Process models to the Monitor server.

### zSplash
This module contains the opening splash screen.

### zSplRes
This module contains the opening splash screen resources.

### zTip
This module contains the Tip Of The Day dialog.

### zWeb
This module contains the web browser view and associated dialogs.

### zWinUtil32
This module contains the basic utility classes and functions related to the 32 bit Windows API.

### zWkf
This module contains the basic workflow system and automation machines.

### zXML
This module contains the basic classes and functions to read from and write to a XML file. <b>NOTE</b> that this module contains no relevant code for now, and is not currently used.
