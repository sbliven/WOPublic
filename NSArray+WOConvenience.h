// NSArray+WOConvenience.h
// WOPublic
//
// Copyright 2006-2009 Wincent Colaiuta. All rights reserved.
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

// system header
#import <Foundation/Foundation.h>

// macro headers
#import "WOConvenienceMacros.h"

WO_DECLARE_CATEGORY_MARKER(NSArray, WOConvenience);

@interface NSArray (WOConvenience)

//! Companion to the lastObject method. Returns nil if the receiver is empty.
- (id)firstObject;

//! Convenience method that allows the creation of more robust, readable tests
//! as shown in this example:
//!
//! \code
//! // easy to make mistakes when coding like this:
//! lastObject = [array objectAtIndex:[array count] - 1];
//!
//! // more robust:
//! if (index == [array lastIndex]) return [array lastObject];
//! \endcode
//!
//! \returns The index of the last item in the receiver, or NSNotFound if the
//! receiver is empty.
- (unsigned)lastIndex;

@end