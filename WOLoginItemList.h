// WOLoginItemList.h
// WOPublic
//
// Copyright 2007-2009 Wincent Colaiuta. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#import "WOObject.h"

@class WOLoginItem;

//! Required classes:
//!     - WOObject (parent class)
//!     - WOLoginItem
//!
@interface WOLoginItemList : WOObject <NSFastEnumeration> {

    LSSharedFileListRef listRef;
    NSMutableArray      *items;
    BOOL                global;

}

+ (WOLoginItemList *)globalLoginItems;

+ (WOLoginItemList *)sessionLoginItems;

- (id)initWithOptions:(CFTypeRef)options;

- (NSArray *)itemsWithName:(NSString *)aName;

- (WOLoginItem *)itemWithPath:(NSString *)aPath;

- (BOOL)removeItemsWithName:(NSString *)aName;

- (BOOL)removeItemWithPath:(NSString *)aPath;

- (BOOL)removeItem:(WOLoginItem *)anItem;

- (BOOL)addItem:(WOLoginItem *)anItem;

#pragma mark -
#pragma mark Properties

@property(copy, readonly)               NSArray *items;
@property(getter=isGlobal, readonly)    BOOL    global;

@end
