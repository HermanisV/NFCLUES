.pragma library

function roundNumber(number, digits)
{
    var multiple = Math.pow(10, digits);
    return Math.round(number * multiple) / multiple;
}

function formatDistance(distance)
{
    if (distance < 1000)
        return distance.toFixed(0) + " m";

    var km = distance/1000;
    if (km < 10)
        return km.toFixed(1) + " km";

    return km.toFixed(0) + " km";
}
