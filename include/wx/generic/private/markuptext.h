///////////////////////////////////////////////////////////////////////////////
// Name:        wx/generic/private/markuptext.h
// Purpose:     Generic wxMarkupText class for managing text with markup.
// Author:      Vadim Zeitlin
// Created:     2011-02-21
// Copyright:   (c) 2011 Vadim Zeitlin <vadim@wxwidgets.org>
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////

#ifndef _WX_GENERIC_PRIVATE_MARKUPTEXT_H_
#define _WX_GENERIC_PRIVATE_MARKUPTEXT_H_

#include "wx/defs.h"

class WXDLLIMPEXP_FWD_CORE wxDC;
class WXDLLIMPEXP_FWD_CORE wxRect;

class wxMarkupParserOutput;

// ----------------------------------------------------------------------------
// wxMarkupText: allows to measure and draw the text containing markup.
// ----------------------------------------------------------------------------

class WXDLLIMPEXP_CORE wxMarkupText
{
public:
    // Constants for Render() flags.
    enum
    {
        Render_Default = 0,     // Don't show mnemonics visually.
        Render_ShowAccels = 1   // Underline mnemonics.
    };


    // Initialize with the given string containing markup (which is supposed to
    // be valid, the caller must check for it before constructing this object).
    //
    // Notice that the usual rules for mnemonics apply to the markup text: if
    // it contains any '&' characters they must be escaped by doubling them,
    // otherwise they indicate that the next character is the mnemonic for this
    // field.
    //
    // TODO-MULTILINE-MARKUP: Currently only single line labels are supported,
    // search for other occurrences of this comment to find the places which
    // need to be updated to support multiline labels with markup.
    wxMarkupText(const wxString& markup)
        : m_markup(markup)
    {
    }

    // Default copy ctor, assignment operator and dtor are ok.

    // Update the markup string.
    //
    // The same rules for mnemonics as in the ctor apply to this string.
    void SetMarkup(const wxString& markup) { m_markup = markup; }

    // This is a convenience method which can be used with the string in which
    // mnemonics should be completely ignored, i.e. not interpreted in any way
    // but just handled as ordinary characters.
    void SetMarkupText(const wxString& markup);


    // Return the width and height required by the given string and optionally
    // the height of the visible part above the baseline (i.e. ascent minus
    // internal leading).
    //
    // The font currently selected into the DC is used for measuring (notice
    // that it is changed by this function but normally -- i.e. if markup is
    // valid -- restored to its original value when it returns).
    wxSize Measure(wxDC& dc, int *visibleHeight = NULL) const;

    // Render the markup string into the given DC in the specified rectangle.
    //
    // Notice that while the function uses the provided rectangle for alignment
    // (it centers the text in it), no clipping is done by it so use Measure()
    // and set the clipping region before rendering if necessary.
    void Render(wxDC& dc, const wxRect& rect, int flags);

    // Similar to Render(), but uses wxRendererNative::DrawItemText() instead
    // of generic wxDC::DrawLabel(), so is more suitable for use in controls
    // that already use DrawItemText() for its items.
    //
    // The meaning of the flags here is different than in the overload above:
    // they're passed to DrawItemText() and Render_ShowAccels is not supported
    // here.
    void RenderItemText(wxWindow *win,
                        wxDC& dc,
                        const wxRect& rect,
                        int rendererFlags);

private:
    wxString m_markup;
};

#endif // _WX_GENERIC_PRIVATE_MARKUPTEXT_H_
