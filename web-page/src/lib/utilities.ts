function isEven(number: number): boolean {
	if (number % 2 === 0) return true;

	return false;
}

export function parseCSV(csv: string): SensorData[] {
	const lines = csv.split('\n');

	const dataSets: SensorData[] = [];

	for (let i = 0; i < lines.length; i++) {
		const fields = lines[i].split(',');

		let currentDataSet: SensorData | undefined;

		for (let j = 0; j < fields.length - 1; j++) {
			if (!isEven(j + 1)) {
				currentDataSet = dataSets.find(({ ID }) => ID === Number(fields[j]));

				if (!currentDataSet) {
					currentDataSet = { ID: Number(fields[j]), data: [] };
					dataSets.push(currentDataSet);
				}
			} else {
				currentDataSet?.data.push({
					y: Number(fields[j]),
					x: Number(fields[fields.length - 1]) * 1000
				});
			}
		}
	}

	return dataSets;
}

export function alignXAxisBegginingEnd(datasets: Dataset[]): Dataset[] {
	let biggestXValue = 0;
	let smallestXValue = Number.MAX_VALUE;

	// Find the biggest and smallest X value
	for (let i = 0; i < datasets.length; i++) {
		const dataArray = datasets[i].data;
		const firstXValue = dataArray[0].x;
		const lastXValue = dataArray[dataArray.length - 1].x;

		if (firstXValue < smallestXValue) {
			smallestXValue = firstXValue;
		}
		if (lastXValue > biggestXValue) {
			biggestXValue = lastXValue;
		}
	}

	// change the first and the last X value to aling the beggining and end of the arrays
	for (let i = 0; i < datasets.length; i++) {
		const dataArray = datasets[i].data;
		const firstDataObject = dataArray[0];
		const lastDataObject = dataArray[dataArray.length - 1];

		if (smallestXValue < firstDataObject.x) {
			firstDataObject.x = smallestXValue;
		}
		if (biggestXValue > lastDataObject.x) {
			lastDataObject.x = biggestXValue;
		}
	}

	return datasets;
}

export function filterDatasetsByDate(datasets: Dataset[], from: string, to: string): Dataset[] {
	if (!from || !to || from.includes('NaN') || to.includes('NaN')) {
		return datasets;
	}

	const splitedFrom = from.split('-');
	const splitedTo = to.split('-');

	const numberSplitedFrom = splitedFrom.map(Number);
	const numberSplitedTo = splitedTo.map(Number);

	const fromDate = new Date(
		numberSplitedFrom[0],
		numberSplitedFrom[1] - 1,
		numberSplitedFrom[2]
	).getTime();
	const toDate = new Date(
		numberSplitedTo[0],
		numberSplitedTo[1] - 1,
		numberSplitedTo[2],
		23,
		59,
		59
	).getTime();

	const filteredDatasets: Dataset[] = [];

	for (let i = 0; i < datasets.length; i++) {
		const data = datasets[i].data;
		const filteredData: Dataset['data'] = [];

		for (let j = 0; j < data.length; j++) {
			if (data[j].x >= fromDate && data[j].x <= toDate) {
				filteredData.push(data[j]);
			} else if (data[j].x > toDate) {
				break;
			}
		}
		filteredDatasets.push({
			label: datasets[i].label,
			borderColor: datasets[i].borderColor,
			data: filteredData
		});
	}
	return filteredDatasets;
}

export function minimum2IntegerDigits(number: number): string {
	return number.toLocaleString('en-US', {
		minimumIntegerDigits: 2,
		useGrouping: false
	});
}
