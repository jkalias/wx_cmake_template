// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/bmpbndl.h>
#include <matplot/matplot.h>

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};
class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size);

private:
    void OnHello(wxCommandEvent &event);
    void OnExit(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);
    wxDECLARE_EVENT_TABLE();
};

enum
{
    ID_Hello = 1
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(ID_Hello, MyFrame::OnHello)
        EVT_MENU(wxID_EXIT, MyFrame::OnExit)
            EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
                wxEND_EVENT_TABLE()
                    wxIMPLEMENT_APP(MyApp);

class MySVGFrame : public wxFrame
{
public:
    explicit MySVGFrame(wxFrame *parent, const wxBitmapBundle &bundle)
        : wxFrame(parent, wxID_ANY, "SVG image",
                  wxDefaultPosition, wxDefaultSize,
                  wxDEFAULT_FRAME_STYLE | wxFULL_REPAINT_ON_RESIZE),
          m_bundle(bundle)
    {
        Bind(wxEVT_PAINT, &MySVGFrame::OnPaint, this);
        SetClientSize(bundle.GetDefaultSize());
    }

private:
    void OnPaint(wxPaintEvent &)
    {
        wxPaintDC dc(this);

        // Check if the bitmap needs to be re-rendered at the new size. Note
        // that the bitmap size is in physical pixels, which can be different
        // from the logical pixels in which the window size is expressed.
        const wxSize sizeWin = GetClientSize();
        const wxSize sizeBmp = sizeWin * GetContentScaleFactor();
        if (!m_bitmap.IsOk() || m_bitmap.GetSize() != sizeBmp)
        {
            m_bitmap = m_bundle.GetBitmap(sizeBmp);
        }

        // Use wxGraphicsContext if available for alpha support.
#if wxUSE_GRAPHICS_CONTEXT
        std::unique_ptr<wxGraphicsContext> const
            gc(wxGraphicsRenderer::GetDefaultRenderer()->CreateContext(dc));

        gc->DrawBitmap(m_bitmap, 0, 0, sizeWin.x, sizeWin.y);
#else
        dc.DrawBitmap(m_bitmap, wxPoint(0, 0), true);
#endif
    }

    const wxBitmapBundle m_bundle;
    wxBitmap m_bitmap;

    wxDECLARE_NO_COPY_CLASS(MySVGFrame);
};

class PNGFrame : public wxFrame
{
public:
    explicit PNGFrame(wxString filename)
        : wxFrame(NULL, wxID_ANY, "PNG image",
                  wxDefaultPosition, wxDefaultSize,
                  wxDEFAULT_FRAME_STYLE | wxFULL_REPAINT_ON_RESIZE),
          m_filename(filename)
    {
        SetBackgroundColour(*wxBLACK);

        // wxImage image(wxT("save.png"), wxBITMAP_TYPE_PNG);
        wxBitmap bitmap(200, 100);
        wxImage image(filename);
        image.LoadFile(m_filename);
        my_png = wxBitmap(image);
        SetClientSize(wxSize(image.GetWidth(), image.GetHeight()));
    }

    void OnPaint(wxPaintEvent &event)
    {
        wxPaintDC dc(this);
        PrepareDC(dc);
        dc.SetTextForeground(*wxBLACK);
        dc.DrawBitmap(my_png, 0, 0);
    }

    wxString m_filename;
    wxBitmap my_png;

private:
    wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(PNGFrame, wxFrame)
    EVT_PAINT(PNGFrame::OnPaint)
        wxEND_EVENT_TABLE()

            bool MyApp::OnInit()
{
    wxImage::AddHandler(new wxPNGHandler);

    const auto filename = "contour.png";
    auto fig = matplot::figure(true);
    // fig->backend()->output("test.svg");

    // auto [x, y, z] = peaks();
    // auto f = contourf(x, y, z);
    auto x = matplot::linspace(-2 * matplot::pi, 2 * matplot::pi);
    auto y = matplot::linspace(0, 4 * matplot::pi);
    auto [X, Y] = matplot::meshgrid(x, y);
    auto Z =
        matplot::transform(X, Y, [](double x, double y)
                           { return sin(x) + cos(y); });
    auto f = matplot::contour(X, Y, Z);
    matplot::save(filename);

    MyFrame *frame = new MyFrame("Hello World", wxPoint(50, 50), wxSize(450, 340));
    frame->Show(false);

    // // // The default size here is completely arbitrary, as we don't know anything
    // // // about the SVG being loaded.
    // wxBitmapBundle bb = wxBitmapBundle::FromSVGFile(filename, wxSize(200, 200));
    // if (!bb.IsOk())
    //     return true;

    // auto canvas = new MySVGFrame(nullptr, bb);
    // canvas->Show();

    auto png_frame = new PNGFrame(wxString("/Users/nemesis/Developer/repos/github/wx_cmake_template/") + filename);
    png_frame->Show(true);

    return true;
}

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
                     "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
    SetMenuBar(menuBar);
    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");
}

void MyFrame::OnExit(wxCommandEvent &event)
{
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent &event)
{
    wxMessageBox("This is a wxWidgets' Hello world sample",
                 "About Hello World", wxOK | wxICON_INFORMATION);
}

void MyFrame::OnHello(wxCommandEvent &event)
{
    wxLogMessage("Hello world from wxWidgets!");
}