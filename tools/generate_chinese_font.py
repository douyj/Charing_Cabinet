#!/usr/bin/env python3

import argparse
from pathlib import Path

from PIL import Image, ImageDraw, ImageFont


FONT_PATHS = [
    "/usr/share/fonts/truetype/droid/DroidSansFallbackFull.ttf",
    "/usr/share/fonts/opentype/noto/NotoSansCJK-Regular.ttc",
]

LATIN_FONT_PATHS = [
    "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
    "/usr/share/fonts/truetype/noto/NotoSans-Regular.ttf",
    "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
]

TEXT = """
智能充电柜终端后台网络在线已连接
设备状态告警状态在线仓位今日订单运行中正常
仓位管理总仓位空闲充电中故障仓位详情当前仓位门锁状态已关闭充电状态所属设备开始充电停止充电打开仓门开门清除告警刷新
充电记录搜索仓位全部状态总记录已完成记录编号开始时间结束时间故障结束已停止
系统日志号仓开始充电充电完成温度异常后台连接正常查看更多
系统设置基础设置设备名称服务器地址服务器端口数据刷新周期秒充电参数满电阈值过温阈值过流阈值自动停止充电已启用系统功能开机自动连接后台告警蜂鸣器本地日志记录测试连接恢复默认保存设置
版本电流电压温度过温已充满
"""

EXTRA = " 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_.,:/%-+[]()<>={}#℃°Ωμ‰²³：，。；、！？·…《》“”‘’"
MATH_SYMBOLS = "+-*/%=<>≤≥≠≈±×÷√∞∑∏∫∂∆∇∈∉∩∪⊂⊃⊆⊇∧∨¬→←↑↓↔"


def parse_args():
    parser = argparse.ArgumentParser(description="Generate an LVGL C font for charging terminal Chinese UI text.")
    parser.add_argument("-s", "--size", type=int, default=16, help="Font size in pixels. Default: 16")
    parser.add_argument("--bpp", type=int, choices=(1, 2, 4), default=4, help="Bits per pixel. Default: 4")
    parser.add_argument("--name", help="Generated lv_font_t object name. Default: font_chinese_<size>")
    parser.add_argument("-o", "--output", type=Path, help="Output C file. Default: src/chinese/<name>.c")
    parser.add_argument("--font", type=Path, help="TTF/TTC font file to render from.")
    parser.add_argument("--latin-font", type=Path, help="TTF font file for ASCII, units, and math symbols.")
    parser.add_argument("--text-file", type=Path, help="Optional UTF-8 file with extra characters to include.")
    parser.add_argument("--extra", default="", help="Extra characters to include.")
    return parser.parse_args()


def pick_font_path(font_path):
    if font_path is not None:
        if font_path.exists():
            return str(font_path)
        raise FileNotFoundError(f"Font not found: {font_path}")

    for path in FONT_PATHS:
        if Path(path).exists():
            return path
    raise FileNotFoundError("No usable CJK font found")


def pick_latin_font_path(font_path):
    if font_path is not None:
        if font_path.exists():
            return str(font_path)
        raise FileNotFoundError(f"Latin font not found: {font_path}")

    for path in LATIN_FONT_PATHS:
        if Path(path).exists():
            return path
    raise FileNotFoundError("No usable Latin/math font found")


def unique_sorted_chars(text):
    chars = set(text)
    chars.discard("\n")
    return sorted(chars, key=ord)


def use_latin_font(ch):
    return ord(ch) < 0x3000 or ch in MATH_SYMBOLS or ch in "℃°Ωμ‰²³"


def pack_4bpp(pixels):
    out = []
    for i in range(0, len(pixels), 2):
        high = pixels[i] >> 4
        low = pixels[i + 1] >> 4 if i + 1 < len(pixels) else 0
        out.append((high << 4) | low)
    return out


def render_glyph(font, ch, ascent):
    if ch == " ":
        adv = max(4, int(round(font.getlength(ch))))
        return [], 0, 0, 0, 0, adv

    bbox = font.getbbox(ch)
    if bbox is None:
        adv = max(1, int(round(font.getlength(ch))))
        return [], 0, 0, 0, 0, adv

    x1, y1, x2, y2 = bbox
    w = max(0, x2 - x1)
    h = max(0, y2 - y1)
    adv = max(1, int(round(font.getlength(ch))))

    if w == 0 or h == 0:
        return [], 0, 0, 0, 0, adv

    img = Image.new("L", (w, h), 0)
    draw = ImageDraw.Draw(img)
    draw.text((-x1, -y1), ch, font=font, fill=255)
    pixels = list(img.getdata())
    return pack_4bpp(pixels), w, h, x1, ascent - y2, adv


def c_array(name, values, per_line=12):
    lines = [f"static const uint8_t {name}[] = {{"]
    for i in range(0, len(values), per_line):
        chunk = values[i:i + per_line]
        lines.append("    " + ", ".join(f"0x{v:02x}" for v in chunk) + ",")
    lines.append("};")
    return "\n".join(lines)


def macro_name(font_name):
    return font_name.upper()


def main():
    args = parse_args()
    if args.size <= 0:
        raise ValueError("--size must be greater than 0")

    font_name = args.name or f"font_chinese_{args.size}"
    output = args.output or Path(f"src/chinese/{font_name}.c")
    text = TEXT + EXTRA + MATH_SYMBOLS + args.extra
    if args.text_file is not None:
        text += args.text_file.read_text(encoding="utf-8")

    font_path = pick_font_path(args.font)
    latin_font_path = pick_latin_font_path(args.latin_font)
    font = ImageFont.truetype(font_path, args.size)
    latin_font = ImageFont.truetype(latin_font_path, args.size)
    ascent, descent = font.getmetrics()
    latin_ascent, _latin_descent = latin_font.getmetrics()
    line_height = ascent + descent
    base_line = descent

    glyph_bitmap = []
    glyph_dsc = [{
        "bitmap_index": 0,
        "adv_w": 0,
        "box_w": 0,
        "box_h": 0,
        "ofs_x": 0,
        "ofs_y": 0,
    }]
    codepoints = []

    for ch in unique_sorted_chars(text):
        glyph_font = latin_font if use_latin_font(ch) else font
        glyph_ascent = latin_ascent if use_latin_font(ch) else ascent
        bitmap, box_w, box_h, ofs_x, ofs_y, adv = render_glyph(glyph_font, ch, glyph_ascent)
        glyph_dsc.append({
            "bitmap_index": len(glyph_bitmap),
            "adv_w": adv * 16,
            "box_w": box_w,
            "box_h": box_h,
            "ofs_x": ofs_x,
            "ofs_y": ofs_y,
        })
        glyph_bitmap.extend(bitmap)
        codepoints.append(ord(ch))

    range_start = min(codepoints)
    unicode_list = [cp - range_start for cp in codepoints]

    dsc_lines = [
        "static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {",
    ]
    for dsc in glyph_dsc:
        dsc_lines.append(
            "    {.bitmap_index = %d, .adv_w = %d, .box_w = %d, .box_h = %d, .ofs_x = %d, .ofs_y = %d},"
            % (
                dsc["bitmap_index"],
                dsc["adv_w"],
                dsc["box_w"],
                dsc["box_h"],
                dsc["ofs_x"],
                dsc["ofs_y"],
            )
        )
    dsc_lines.append("};")

    unicode_lines = [
        "static const uint16_t unicode_list_0[] = {",
    ]
    for i in range(0, len(unicode_list), 12):
        chunk = unicode_list[i:i + 12]
        unicode_lines.append("    " + ", ".join(str(v) for v in chunk) + ",")
    unicode_lines.append("};")

    content = f"""/*******************************************************************************
 * Size: {args.size} px
 * Bpp: {args.bpp}
 * CJK font: {font_path}
 * Latin/math font: {latin_font_path}
 * Symbols: generated from charging terminal UI screenshots.
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
    #include \"lvgl.h\"
#else
    #include \"../../lib/lvgl/lvgl.h\"
#endif

#ifndef {macro_name(font_name)}
    #define {macro_name(font_name)} 1
#endif

#if {macro_name(font_name)}

#include \"src/font/lv_font_fmt_txt.h\"

{c_array("glyph_bitmap", glyph_bitmap)}

{chr(10).join(dsc_lines)}

{chr(10).join(unicode_lines)}

static const lv_font_fmt_txt_cmap_t cmaps[] = {{
    {{
        .range_start = {range_start}, .range_length = {max(codepoints) - range_start + 1}, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = {len(codepoints)}, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }}
}};

static lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {{
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = {args.bpp},
    .kern_classes = 0,
    .bitmap_format = 0,
    .cache = &cache
}};

const lv_font_t {font_name} = {{
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,
    .line_height = {line_height},
    .base_line = {base_line},
    .subpx = LV_FONT_SUBPX_NONE,
    .underline_position = -2,
    .underline_thickness = 1,
    .dsc = &font_dsc
}};

#endif
"""

    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(content, encoding="utf-8")
    print(f"generated {output} as {font_name} with {len(codepoints)} glyphs")


if __name__ == "__main__":
    main()
