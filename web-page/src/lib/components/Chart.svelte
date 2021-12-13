<script lang="ts">
	import {
		Chart,
		LineElement,
		LineController,
		TimeScale,
		TimeSeriesScale,
		Legend,
		LinearScale,
		Title,
		Tooltip,
		PointElement,
		Decimation
	} from 'chart.js/dist/chart.esm';

	Chart.register(
		LineElement,
		LineController,
		LinearScale,
		TimeScale,
		PointElement,
		TimeSeriesScale,
		Legend,
		Title,
		Tooltip,
		Decimation
	);
	import 'chartjs-adapter-date-fns';
	import { onMount } from 'svelte';

	export let title: string;
	export let min: number;
	export let max: number;
	export let datasets: Dataset[];
	let canvas: HTMLCanvasElement;

	const colors = {
		primaryColor1: '#191a19',
		primaryColor2: '#323937',
		textColor: '#ebecde',
		secondaryColor: '#4a5b5b',
		accentColor: '#4e9f3d'
	};

	Chart.defaults.color = colors.textColor;
	let chart: Chart<
		'line',
		{
			x: number;
			y: number;
		}[],
		unknown
	>;

	onMount(() => {
		chart = new Chart(canvas, {
			type: 'line',

			data: {
				datasets: datasets
			},
			options: {
				normalized: true,
				animation: false,
				spanGaps: true,
				plugins: {
					title: {
						font: { size: 32 },
						display: true,
						text: title
					},
					decimation: {
						enabled: true, //Reduce the number of points to draw,
						algorithm: 'lttb'
					}
				},
				datasets: {
					line: {
						pointRadius: 0, //Disable drawing points
						borderCapStyle: 'round',
						borderJoinStyle: 'round',
						borderWidth: 2
					}
				},
				scales: {
					y: {
						beginAtZero: true,
						min: min,
						max: max,
						grid: {
							color: colors.secondaryColor,
							borderColor: colors.textColor
						}
					},
					x: {
						type: 'time',
						grid: {
							color: colors.secondaryColor,
							borderColor: colors.textColor
						},
						ticks: {
							color: colors.textColor
						},
						time: {
							tooltipFormat: 'dd-MM-yyyy HH:mm',
							displayFormats: {
								millisecond: 'HH:mm:ss.SSS',
								second: 'HH:mm:ss',
								minute: 'HH:mm',
								hour: 'HH'
							}
						}
					}
				}
			}
		});
		chart.render();
	});

	$: if (chart) {
		chart.data.datasets = datasets;
		chart.update();
	}
</script>

<canvas height="500" width="1000" bind:this={canvas} />

<style>
	canvas {
		width: 100%;
		height: 100%;
	}
</style>
