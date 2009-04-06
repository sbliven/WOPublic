// WOArgumentArray.m
// WODebug
//
// Copyright 2006-2009 Wincent Colaiuta.

// class header
#import "WOArgumentArray.h"

@implementation WOArgumentArray

+ (id)arrayWithArray:(NSArray *)anArray
{
    return [[self alloc] initWithArray:anArray];
}

- (id)initWithArray:(NSArray *)anArray
{
    if ((self = [super init]))
        [self setArguments:anArray];
    return self;
}

- (unsigned)count
{
    return (arguments ? [arguments count] : 0);
}

- (NSString *)argumentForOption:(NSString *)option
{
    // example:
    // argumentForOption:@"foo"         : --foo= returns @"" (empty string)
    //                                  : --foo returns nil (malformed)
    //                                  : --no-foo=bar returns nil (malformed)
    //                                  : --foo=bar returns @"bar"
    //                                  : foo=bar returns nil (malformed)
    // argumentForOption:@"bb"          : -bb val returns nil (malformed)
    // argumentForOption:@"b"           : -b val returns @"val"
    //                                  : -b -val returns nil (missing)
    //                                  : b val returns nil (malformed)
    //
    if (option == nil) return nil;
    for (unsigned i = 0, max = [self count]; i < max; i++)
    {
        NSString *arg = [self argumentAtIndex:i];
        unsigned int length = [arg length];
        if ([arg hasPrefix:@"--no-"]) // long option, boolean NO (malformed)
            continue;
        else if ([arg hasPrefix:@"--"]) // long option
        {
            // parse: key=value
            NSArray *components =
                [[arg substringFromIndex:2] componentsSeparatedByString:@"="];
            if ([components count] != 2) continue;
            if ([[components objectAtIndex:0] isEqualToString:option])
                return [components objectAtIndex:1];
        }
        else if ([arg hasPrefix:@"-"]) // short option
        {
           if ((length == 2) && // marker plus exactly one letter
                [option isEqualToString:[arg substringFromIndex:1]])
            {
                // match found; peek at next argument
                if ((i + 1) < max)
                {
                    if (![self argumentIsOptionAtIndex:(i + 1)])
                        return [self argumentAtIndex:(i + 1)];
                }
                else
                    return nil; // no next argument!
            }
        }
    }
    return nil; // fallback case
}

- (BOOL)boolForOption:(NSString *)option
{
    // examples:
    // boolForOption:@"b"       : -b would return YES
    //                          : --b would return NO (malformed, long-form options must be words)
    //                          : b would return NO (malformed)
    // boolForOption:@"expand"  : --no-expand=foo (malformed, not a BOOL) would return NO
    //                          : --expand=foo (malformed, not a BOOL) would return NO
    //                          : --expand would return YES
    //                          : --no-expand would return NO
    //                          : expand would return NO (malformed)
    // boolForOption:@"---"     : would work, we don't really enforce what a valid option name is
    // boolForOption:@"expand=" : once again, invalid for a BOOL but we don't enforce
    // boolForOption:@"expand=NO"   : again, no enforcement
    //
    if (option == nil) return NO;
    for (NSString *arg in arguments)
    {
        unsigned int length = [arg length];
        if ([arg hasPrefix:@"--no-"]) // long option, boolean NO
        {
            if ((length > 6) && // marker plus at least two letters
                [option isEqualToString:[arg substringFromIndex:5]])
                return NO; // (negative) match found!
        }
        else if ([arg hasPrefix:@"--"]) // long option, boolean YES
        {
            if ((length > 3) && // marker plus at least two letters
                [option isEqualToString:[arg substringFromIndex:2]])
                return YES; // (positive) match found
        }
        else if ([arg hasPrefix:@"-"]) // short option
        {
            if ((length == 2) && // marker plus exactly one letter
                [option isEqualToString:[arg substringFromIndex:1]])
                return YES; // (positive) match found
        }
    }
    return NO; // fallback case
}

- (NSString *)argumentAtIndex:(unsigned)index;
{
    NSAssert(arguments != nil, @"argumentAtIndex: arguments is nil");
    if (index >= [arguments count])
        [NSException raise:NSRangeException
                    format:@"argumentAtIndex: illegal index %d", index];
    return [arguments objectAtIndex:index];
}

- (NSArray *)argumentsFromIndex:(unsigned)index
{
    NSAssert(arguments != nil, @"argumentFromIndex: arguments is nil");
    if (index >= [arguments count])
        [NSException raise:NSRangeException
                    format:@"argumentAtIndex: illegal index %d", index];
    return [arguments subarrayWithRange:
        NSMakeRange(index, [arguments count] - index)];
}

- (BOOL)argumentIsOptionAtIndex:(unsigned)index
{
    // rely on argumentAtIndex to throw an exception if appropriate
    return ([[self argumentAtIndex:index] hasPrefix:@"-"] ? YES : NO);
}

#pragma mark -
#pragma mark Accessors

- (NSArray *)arguments
{
    return arguments;
}

- (void)setArguments:(NSArray *)anArguments
{
    if (arguments != anArguments)
        arguments = anArguments;
}

@end
