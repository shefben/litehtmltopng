#include "php_litehtmltopng.h"
#include <litehtml.h>
#include "../libs/litehtmlcpp98/containers/cairo_ft/container_cairo_ft.h"
#include <cairo.h>
#include <fstream>
#include <string>

class php_device_container : public container_cairo_ft
{
public:
    php_device_container(const std::string& root, int width = 384, int dpi = 96)
        : m_root(root), m_width(width), m_dpi(dpi) {}
    virtual ~php_device_container() {}
protected:
    virtual int device_width_px() const { return m_width; }
    virtual int device_resolution_dpi() const { return m_dpi; }
    virtual std::string path_root_resources() const { return m_root; }
private:
    std::string m_root;
    int m_width;
    int m_dpi;
    virtual void make_url(const litehtml::tchar_t* url, const litehtml::tchar_t* basepath, litehtml::tstring& out) override
    {
        out = m_root + url;
    }
    virtual void get_client_rect(litehtml::position& client) const override
    {
        client = litehtml::position(0, 0, m_width, 0);
    }
    virtual void get_media_features(litehtml::media_features& media) const override
    {
        litehtml::position client;
        get_client_rect(client);
        media.type = litehtml::media_type_screen;
        media.width = client.width;
        media.height = client.height;
        media.device_width = m_width;
        media.device_height = client.height;
        media.color = 8;
        media.monochrome = 0;
        media.color_index = 256;
        media.resolution = m_dpi;
    }
    virtual void set_caption(const litehtml::tchar_t* caption) override {}
    virtual void set_base_url(const litehtml::tchar_t* base_url) override {}
    virtual void import_css(litehtml::tstring& text, const litehtml::tstring& url, litehtml::tstring& baseurl) override
    {
        std::ifstream t(m_root + url);
        if (t.is_open())
        {
            text.assign((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
        }
    }
    virtual void on_anchor_click(const litehtml::tchar_t* url, const litehtml::element::ptr& el) override {}
    virtual void set_cursor(const litehtml::tchar_t* cursor) override {}
};

int litehtmltopng_render_file(const char* html_file, const char* output_file)
{
    std::ifstream html(html_file);
    if(!html.is_open()) {
        return -1;
    }
    std::string html_text((std::istreambuf_iterator<char>(html)), std::istreambuf_iterator<char>());

    std::string root = "./";
    std::string path(html_file);
    auto pos = path.find_last_of('/');
    if(pos != std::string::npos) {
        root = path.substr(0, pos + 1);
    }

    php_device_container container(root);
    litehtml::context ctx;

    std::ifstream css(root + "master.css");
    if(css.is_open()) {
        std::string css_text((std::istreambuf_iterator<char>(css)), std::istreambuf_iterator<char>());
        ctx.load_master_stylesheet(css_text.c_str());
    }

    auto doc = litehtml::document::createFromUTF8(html_text.c_str(), &container, &ctx);
    doc->render(container.device_width_px());
    int width = doc->width();
    int height = doc->height();

    cairo_surface_t* surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
    cairo_t* cr = cairo_create(surface);
    cairo_rectangle(cr, 0, 0, width, height);
    cairo_clip(cr);
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_paint(cr);
    litehtml::position clip(0,0,width,height);
    doc->draw((litehtml::uint_ptr)cr, 0, 0, &clip);

    cairo_status_t status = cairo_surface_write_to_png(surface, output_file);
    cairo_destroy(cr);
    cairo_surface_destroy(surface);
    return status == CAIRO_STATUS_SUCCESS ? 0 : -1;
}

