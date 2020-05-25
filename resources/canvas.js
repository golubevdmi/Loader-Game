
function drawSprite(ctx, img, width, height)
{
    if (!img)
        return;
    var sz = Math.min(width, height);

    var x = 0;
    var y = 0;
    if (width > height)
        x = (width - height) / 2;
    else if (height > width)
        y = (height - width) / 2;

    ctx.drawImage(img, x, y, sz, sz);
}
